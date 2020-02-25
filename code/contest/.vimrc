set cin wmnu sc nu ts=4 sw=4 tm=1000 vb sm aw ai ru cul mouse=a ar cb=unnamed bs=indent,eol,start nowrap hls is sta t_vb=
map <F4> :<C-U>!g++ -Wall -Wextra -Wshadow -O -std=c++17 % -o %:r && ./%:r < input.txt > output.txt <CR>
let mapleader=","
nnoremap <leader><space> :nohlsearch<CR>
nnoremap <leader>` :e $MYVIMRC<CR>

