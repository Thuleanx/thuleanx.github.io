---
layout: post
title: "Bebop Baton"
image: 
    thumbnail: /assets/images/gameCaptures/bebop-baton/attackcombo3.gif
sidebar:
    image: /assets/images/gameCaptures/bebop-baton/title.png
    team: 2
    tools: Unity, FMOD, Reaper
    duration: 1 week
    platforms: MacOS, Windows, and WebGL
    text: >-

        - Beatmapping tool

        - State-machine animation and AI

        - Input buffering

        - Parry system
    links:
      - title: "Itch"
        url: "https://ayucinna.itch.io/bebop-baton"
        icon: "fab fa-gamepad fa"
      - title: "Github"
        url: "https://github.com/Thuleanx/RhythmGameJam"
        icon: "fa fa-github-alt"
permalink: /games/bebop-baton/
no_masthead: true

gallery1:
  - image_path: /assets/images/gameCaptures/doomolish/round2.gif
  - image_path: /assets/images/gameCaptures/doomolish/round3.gif

---

Bebop Baton is a 3D action rhythm game that won first place in 
[Rhythm Jam 2024](https://itch.io/jam/rhythm-jam-2024).
Technical artist [Allison Yeh](https://allisonkyeh.com/) handles everything
art and sound design, while I focused on the gameplay side.

{% include image-collection.html class='half' images="
    /assets/images/gameCaptures/bebop-baton/attackcombo4_enemydeath.gif,
    /assets/images/gameCaptures/bebop-baton/enemystun_shieldup2.gif" %}

Some time ago, I remember hearing someone describe Sekiro as a rhythm game
and the idea stuck in my head. 
For this jam, we set out to make a jazz-themed rhythm game where you need to parry
in sync with the song's notes.

{% include image-collection.html class='third' images="
    /assets/images/gameCaptures/bebop-baton/title.gif,
    /assets/images/gameCaptures/bebop-baton/attackparries1.gif,
    /assets/images/gameCaptures/bebop-baton/gameover.gif" %}

---

# Beatmap

There's not enough time to make robust beatmapping tool during the jam, so 
I had to get creative with another option:
mapping out the song in my DAW by placing 'A' notes
where beats should be, outputting that into a MIDI file, and parsing in 
Unity with `DryWetMidi`:

```c++
static (MidiFile, List<MidiNote>, Playback) ReadMidiFile(string filePath) {
    MidiFile file = MidiFile.Read(
        Path.Combine(Application.streamingAssetsPath, filePath));

    List<MidiNote> notes = new List<MidiNote>(file.GetNotes());
    notes.Sort((a, b) => {
        return (int) (a.Time - b.Time);
    });

    Playback playback = file.GetPlayback(OutputDevice.GetByName(
        "Microsoft GS Wavetable Synth")
    );

    return (file, notes, playback);
}
```

The notes are stored in a list sorted by their event time. 
When a song plays I can emit beat events when the playback time exceeds a certain
note's time:
```c++
while (noteIndex < notes.Count) {
    MidiNote note = notes[noteIndex];

    MetricTimeSpan timeSpan = note
        .TimeAs<MetricTimeSpan>(midiFile.GetTempoMap());

    double noteTime = timeSpan.TotalMilliseconds;

    if (noteTime > songCurrentTime) break;

    const float MS_IN_SECOND = 1000;

    GameGlobals.Note.Raise(new Audio.NoteInformation(
        TimeSinceNote: (float) (songCurrentTime - noteTime) / MS_IN_SECOND,
        NoteNumber: (int) note.NoteNumber
    ));

    noteIndex++;
}
```

---

# Gameplay

{% include image-collection.html class='third' images="
    /assets/images/gameCaptures/bebop-baton/attackcombo3.gif,
    /assets/images/gameCaptures/bebop-baton/enemyattack1.gif,
    /assets/images/gameCaptures/bebop-baton/enemyblock1.gif" %}

![enemy attack](/assets/images/gameCaptures/bebop-baton/attackcombo4_enemydeath.gif){:.align-left}
Handling parries in a rhythm game turns out to be a tricky operation.
To demonstrate, here's the list of things that we have to account for:
1. If you hit attack off beat, your character is stunned
2. If you hit an attack on beat, but the enemy does not attack, the enemy parries and block said attack
3. If you hit an attack when an enemy attack (on beat & on a note determined by the beatmap), then you perform a parry 
4. Perform enough (4) parries and the enemies will enter a poise broken state. In this state, any on-beat input will result in
an unguarded attack against them

To add complexity, your timing can be slightly before or slightly after a beat, 
and this leniency window is wide enough so that concurrent windows might overlap and even 
overlap the preceding / next beat.
This means that it's possible to hit parry twice right before a beat, and parry the attack 
happening on said beat and the next.

## Input buffering

To accomodate this design, we need to buffer our inputs similar to a fighting game.
Every parry input goes into a queue, along with the input time:
```c++
void OnAttackInput(bool attackDown) { 
    if (!attackDown || !Musician.IsPlaying) return; 

    InputQueue.Enqueue(new PlayerInput(
        beatCurrentTime,
        PlayerInput.InputType.ATTACK
    ));
}
```
and the beats themselves are also queued up in a similar manner, although all beats 
are preloaded into the queue. We can peek into these queues, see if the top entries
are close enough in time, and if so register that as a parry:
```c++
public HitAccuracy GetAccuracy(TimeMarker note, double hit) {
    double diff = System.Math.Abs(note.Miliseconds - hit);
    if (diff < perfectTimeWindowMiliseconds) 
        return HitAccuracy.PERFECT;
    if (diff < goodTimeWindowMiliseconds)
        return HitAccuracy.HIT;
    return HitAccuracy.MISS;
}

HitAccuracy GetParryAccuracy() {
    while (beatQueue.Queue.Count > 0) {
        bool canBeParried = beatQueue.Queue.Peek().time.Seconds - windupSignalSeconds
            > InputQueue.Peek().Seconds;
        if (canBeParried) break;
        beatQueue.Queue.Pop();
    }

    if (beatQueue.Queue.Count == 0) 
        return HitAccuracy.MISS;

    Beat beat = beatQueue.Queue.Peek();

    return GetAccuracy(InputQueue.Peek(), beat.time);
}
```

Then, the high level of our `Update` function is as follows:
```c++
while (InputQueue.Count > 0) {
    HitAccuracy accuracy = GetParryAccuracy();

    if (accuracy == HitAccuracy.MISS) {
        int BeatIndex = beatCurrentTime.ClosestBeatAsInt;

        BeatTimeMarker OnBeatMarker = BeatTimeMarker.FromBeatIndex(
            BeatsPerMinute, BeatIndex);

        HitAccuracy parryAccuracy = GetAccuracy(OnBeatMarker, beatCurrentTime);

        bool didPlayerMissBeat = lastParriedBeatIndex >= BeatIndex 
            || parryAccuracy == HitAccuracy.MISS 
            || BeatIndex % GameGlobals.BeatDivision != 0;

        // Stun player if miss timing
        if (didPlayerMissBeat) {
            router.SignalParryTimingMissed(shouldStunPlayer: true);
        } else {
            if (focusedTarget && !focusedTarget.IsPoiseBroken) {
                // Miss parry, enemy will block
                router.SignalParryTimingMissed(shouldStunPlayer: false);
            } else {
                // If enemy is poise broken, we can parry / attack them
                router.SignalParry(BeatIndex, parryAccuracy, true, focusedTarget);
            }
        }

    } else {
        Beat beat = beatQueue.Queue.Peek();

        // Successful parry
        router.SignalParry(beat.Channel, beat.time.BeatAsInt, accuracy);
        lastParriedBeatIndex = beat.time.BeatAsInt;

        beatQueue.Queue.Pop();
    }

    InputQueue.Deque();
}
```

## Animation

![enemy attack](/assets/images/gameCaptures/bebop-baton/attackcombo3.gif){:.align-right}
To complicate things, we need to also account for animation delays. 
Both enemy and player has a windup attack & parry that needs to line up 
closely with the beat. 
But not all windup animations during the course of play are the same. 
The player might press parry 4 frames early, 2 frames early, or late.
In the first two cases we need to start playing the windup and immediately transition
to the wind-down animation when the beat happens.

![enemy attack](/assets/images/gameCaptures/bebop-baton/enemyattack2.gif){:.align-left}
Enemies also cannot immediately play the hit vfx or apply damage when the beat happens, since the player
can parry late.
Instead, this happens at a slight delay once it's confirmed that the parry is impossible, as shown below:

The fact that Bebop-Baton's gameplay is in the form of combat also presents its own challenges.
In a regular lane-based rhythm game, missed notes can be immediately be displayed
as a miss then discarded from the lane.
In BeBop Baton, suppose 5 notes come in quick succession and you miss the 5th,
the system needs to keep track of the missed parry until finished with playing those 4 successful 
parry animations.

The code for this is admittedly too hacky and inellegant to show here, but feel free to 
dig through `Scripts/Gameplay/Components/Audio/Conductor.cs` on the github repository if you are curious.
