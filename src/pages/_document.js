import { Html, Head, Main, NextScript } from 'next/document'
import AllImports from '../modules/import.js'

export default function Document() {
  return (
    <Html lang="en">
      <Head>
        <AllImports/>
      </Head>
      <body>
        <Main />
        <NextScript />
      </body>
    </Html>
  )
}
