/** @type {import('next').NextConfig} */
const nextConfig = {
    reactStrictMode: true,
    images: {
        remotePatterns: [
            {
                protocol: 'https',
                hostname: '**.com',
            },
            {
                protocol: 'https',
                hostname: '**.net',
            },
        ]
    },
    // async rewrites() {
    //     return [
    //         {
    //             source: "/saga",
    //             destination: "/saga/index.html"
    //         },
    //     ]
    // },
}

module.exports = nextConfig
