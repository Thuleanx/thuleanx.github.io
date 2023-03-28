import Head from 'next/head'
import Image from 'next/image'
import { Inter } from 'next/font/google'
import styles from '@/styles/Home.module.css'

const inter = Inter({ subsets: ['latin'] })

export default function Home() {
  return (
    <>
      <main className={styles.main}>
        Hi this is my website. <br/>
        It`&apos;`s nearly complete. Can`&apos;`t you tell.
<article>
  <h2 className="f3 fw4 pa3 mv0">Albums</h2>
  <div className="cf pa2">
    <div className="fl w-50 w-25-m w-20-l pa2">
      <a href="https://geo.itunes.apple.com/us/album/blonde/id1146195596?at=1l3vqFJ&mt=1&app=music" className="db link dim tc">
        <img src="https://img.pokemondb.net/artwork/large/pikachu.jpg" alt="Frank Ocean Blonde Album Cover" className="w-100 db outline black-10"/>
        <dl className="mt2 f6 lh-copy">
          <dt className="clip">Title</dt>
          <dd className="ml0 black truncate w-100">Blonde</dd>
          <dt className="clip">Artist</dt>
          <dd className="ml0 gray truncate w-100">Frank Ocean</dd>
        </dl>
      </a>
    </div>
    <div className="fl w-50 w-25-m w-20-l pa2">
      <a href="https://geo.itunes.apple.com/us/album/jeffery/id1146718343?at=1l3vqFJ&mt=1&app=music" className="db link dim tc">
        <img src="https://img.pokemondb.net/artwork/large/pikachu.jpg" alt="Young Thug - Jeffery Album Cover" className="w-100 db outline black-10"/>
        <dl className="mt2 f6 lh-copy">
          <dt className="clip">Title</dt>
          <dd className="ml0 black truncate w-100 ttu">Jeffery</dd>
          <dt className="clip">Artist</dt>
          <dd className="ml0 gray truncate w-100">Young Thug</dd>
        </dl>
      </a>
    </div>
    <div className="fl w-50 w-25-m w-20-l pa2">
      <a href="https://geo.itunes.apple.com/us/album/untitled-unmastered./id1089846273?at=1l3vqFJ&mt=1&app=music" className="db link dim tc">
        <img src="https://img.pokemondb.net/artwork/large/pikachu.jpg" alt="Kendrick Lamar untitled unmastered. Album Cover" className="w-100 db outline black-10"/>
        <dl className="mt2 f6 lh-copy">
          <dt className="clip">Title</dt>
          <dd className="ml0 black truncate w-100">untitled umastered.</dd>
          <dt className="clip">Artist</dt>
          <dd className="ml0 gray truncate w-100">Kendrick Lamar</dd>
        </dl>
      </a>
    </div>
    <div className="fl w-50 w-25-m w-20-l pa2">
      <a href="https://geo.itunes.apple.com/us/album/99.9/id1092026376?at=1l3vqFJ&mt=1&app=music" className="db link dim tc">
        <img src="https://img.pokemondb.net/artwork/large/pikachu.jpg" alt="Kaytranada 99%" className="w-100 db outline black-10"/>
        <dl className="mt2 f6 lh-copy">
          <dt className="clip">Title</dt>
          <dd className="ml0 black truncate w-100">99%</dd>
          <dt className="clip">Artist</dt>
          <dd className="ml0 gray truncate w-100">Kaytranada</dd>
        </dl>
      </a>
    </div>
    <div className="fl w-50 w-25-m w-20-l pa2">
      <a href="https://geo.itunes.apple.com/us/album/aa/id1067924003?at=1l3vqFJ&mt=1&app=music" className="db link dim tc">
        <img src="https://img.pokemondb.net/artwork/large/pikachu.jpg" alt="Baauer Aa - Album Cover" className="w-100 db outline black-10"/>
        <dl className="mt2 f6 lh-copy">
          <dt className="clip">Title</dt>
          <dd className="ml0 black truncate w-100">Aa</dd>
          <dt className="clip">Artist</dt>
          <dd className="ml0 gray truncate w-100">Baauer</dd>
        </dl>
      </a>
    </div>
    <div className="fl w-50 w-25-m w-20-l pa2">
      <a href="https://geo.itunes.apple.com/us/album/99-cents/id1054734475?at=1l3vqFJ&mt=1&app=music" className="db link dim tc">
        <img src="https://img.pokemondb.net/artwork/large/pikachu.jpg" alt="Santigold 99 cents - Album cover" className="w-100 db outline black-10"/>
        <dl className="mt2 f6 lh-copy">
          <dt className="clip">Title</dt>
          <dd className="ml0 black truncate w-100">99 cents</dd>
          <dt className="clip">Artist</dt>
          <dd className="ml0 gray truncate w-100">Santigold</dd>
        </dl>
      </a>
    </div>
    <div className="fl w-50 w-25-m w-20-l pa2">
      <a href="https://geo.itunes.apple.com/us/album/a-moon-shaped-pool/id1111577743?at=1l3vqFJ&mt=1&app=music" className="db link dim tc">
        <img src="https://img.pokemondb.net/artwork/large/pikachu.jpg" alt="A Moon Shaped Pool - Album cover" className="w-100 db outline black-10"/>
        <dl className="mt2 f6 lh-copy">
          <dt className="clip">Title</dt>
          <dd className="ml0 black truncate w-100">A Moon Shaped Pool</dd>
          <dt className="clip">Artist</dt>
          <dd className="ml0 gray truncate w-100">Radiohead</dd>
        </dl>
      </a>
    </div>
    <div className="fl w-50 w-25-m w-20-l pa2">
      <a href="https://geo.itunes.apple.com/us/album/the-life-of-pablo/id1123231885?at=1l3vqFJ&mt=1&app=music" className="db link dim tc">
        <img src="https://img.pokemondb.net/artwork/large/pikachu.jpg" alt="The Life of Pablo - Album Cover" className="w-100 db outline black-10"/>
        <dl className="mt2 f6 lh-copy">
          <dt className="clip">Title</dt>
          <dd className="ml0 black truncate w-100">The Life of Pablo</dd>
          <dt className="clip">Artist</dt>
          <dd className="ml0 gray truncate w-100">Kanye West</dd>
        </dl>
      </a>
    </div>
    <div className="fl w-50 w-25-m w-20-l pa2">
      <a href="https://geo.itunes.apple.com/us/album/coloring-book/id1113239004?at=1l3vqFJ&mt=1&app=music" className="db link dim tc">
        <img src="https://img.pokemondb.net/artwork/large/pikachu.jpg" alt="Coloring Book - Album cover" className="w-100 db outline black-10"/>
        <dl className="mt2 f6 lh-copy">
          <dt className="clip">Title</dt>
          <dd className="ml0 black truncate w-100">Coloring Book</dd>
          <dt className="clip">Artist</dt>
          <dd className="ml0 gray truncate w-100">Chance the Rapper</dd>
        </dl>
      </a>
    </div>
    <div className="fl w-50 w-25-m w-20-l pa2">
      <a href="https://geo.itunes.apple.com/us/album/everybody-looking/id1135576036?at=1l3vqFJ&mt=1&app=music" className="db link dim tc">
        <img src="https://img.pokemondb.net/artwork/large/pikachu.jpg" alt="Everybody Looking - Album Cover" className="w-100 db outline black-10"/>
        <dl className="mt2 f6 lh-copy">
          <dt className="clip">Title</dt>
          <dd className="ml0 black truncate w-100">Everybody Looking</dd>
          <dt className="clip">Artist</dt>
          <dd className="ml0 gray truncate w-100">Gucci Mane</dd>
        </dl>
      </a>
    </div>
  </div>
</article>
      </main>
    </>
  )
}
