export default function ShowcaseContainer ({title, children}) {
    return ( 
        <article>
            <h2 className="f3 fw4 pa3 mv0">{title}</h2>
            <div className="cf pa2">
                {children}
            </div>
        </article>
    );
}
