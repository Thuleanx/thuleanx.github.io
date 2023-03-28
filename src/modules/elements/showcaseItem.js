import Image from 'next/image'

export default function showcaseItem({href, src, title, subtitle}) {
    // <Image src={src} alt="nothing" fill object-fit="contain" className="w-100 db outline black-10" />
    return (
        <div className="fl w-50 w-25-m w-20-l pa2">
            <a href={href} className="db link dim tc">
                <img src={src} alt="something" className="w-100 db outline black-10"/>
                <dl className="mt2 f6 lh-copy">
                <dt className="clip">{title}</dt>
                <dd className="ml0 black truncate w-100">{title}</dd>
                <dt className="clip">{subtitle}</dt>
                <dd className="ml0 gray truncate w-100">{title}</dd>
                </dl>
            </a>
        </div>
    );
}
