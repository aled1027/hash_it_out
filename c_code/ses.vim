let SessionLoad = 1
if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
imap <S-Tab> <Plug>snipMateBack
inoremap <silent> <SNR>77_yrrecord =YRRecord3()
inoremap <silent> <Plug>NERDCommenterInsert  <BS>:call NERDComment('i', "insert")
inoremap <silent> <Plug>snipMateShow =snipMate#ShowAvailableSnips()
inoremap <silent> <Plug>snipMateBack =snipMate#BackwardsSnippet()
inoremap <silent> <Plug>snipMateTrigger =snipMate#TriggerSnippet(1)
inoremap <silent> <Plug>snipMateNextOrTrigger =snipMate#TriggerSnippet()
nnoremap <silent>  :CtrlP
nnoremap  :CtrlPTag
nnoremap  
xmap 	 <Plug>snipMateVisual
smap 	 <Plug>snipMateNextOrTrigger
nnoremap <NL> <NL>
nnoremap  
nnoremap  
xnoremap <silent>  :call multiple_cursors#new("v", 0)
nnoremap <silent>  :YRReplace '1', 'p'
nnoremap <silent>  :YRReplace '-1', 'P'
nnoremap  :call GotoFile("new")
nnoremap f :call GotoFile("new")
nmap  ca <Plug>NERDCommenterAltDelims
xmap  cu <Plug>NERDCommenterUncomment
nmap  cu <Plug>NERDCommenterUncomment
xmap  cb <Plug>NERDCommenterAlignBoth
nmap  cb <Plug>NERDCommenterAlignBoth
xmap  cc <Plug>NERDCommenterAlignLeft
nmap  cc <Plug>NERDCommenterAlignLeft
nmap  cA <Plug>NERDCommenterAppend
xmap  cy <Plug>NERDCommenterYank
nmap  cy <Plug>NERDCommenterYank
xmap  cs <Plug>NERDCommenterSexy
nmap  cs <Plug>NERDCommenterSexy
xmap  ci <Plug>NERDCommenterInvert
nmap  ci <Plug>NERDCommenterInvert
nmap  c$ <Plug>NERDCommenterToEOL
xmap  cn <Plug>NERDCommenterNested
nmap  cn <Plug>NERDCommenterNested
xmap  cm <Plug>NERDCommenterMinimal
nmap  cm <Plug>NERDCommenterMinimal
xmap  c  <Plug>NERDCommenterToggle
nmap  c  <Plug>NERDCommenterToggle
xmap  cl <Plug>NERDCommenterComment
nmap  cl <Plug>NERDCommenterComment
nnoremap  c :call CommentWithSlashes()
map  t  :tabnext
map  tm :tabmove
map  tc :tabclose
map  to :tabonly
map  tn :tabnew
nnoremap  sv :source $MYVIMRC
nnoremap  ev :vsplit $MYVIMRC
vnoremap  z zf
nnoremap  z za
nmap <silent>  rv <Plug>SetTmuxVars
nmap <silent>  rs <Plug>NormalModeSendToTmux
vmap <silent>  rs <Plug>SendSelectionToTmux
vmap + <Plug>(expand_region_expand)
nmap + <Plug>(expand_region_expand)
nmap 0 ^
vmap 0 ^
xnoremap <silent> P :YRPaste 'P', 'v'
nnoremap <silent> P :YRPaste 'P'
xmap S <Plug>VSurround
vmap Si S(i_f)
nmap \\u <Plug>CommentaryUndo:echomsg '\\ is deprecated. Use gc'
nmap \\\ <Plug>CommentaryLine:echomsg '\\ is deprecated. Use gc'
nmap \\ :echomsg '\\ is deprecated. Use gc'<Plug>Commentary
xmap \\ <Plug>Commentary:echomsg '\\ is deprecated. Use gc'
map \t :VimuxRunLastCommand
map \nf :NERDTreeFind
map \nb :NERDTreeFromBookmark 
map \nn :NERDTreeToggle
map \o :BufExplorer
nmap _ <Plug>(expand_region_shrink)
vmap _ <Plug>(expand_region_shrink)
map bd :bdelete
map bN :bprev
map bn :bnext
nmap cS <Plug>CSurround
nmap cs <Plug>Csurround
nmap cgc <Plug>ChangeCommentary
xnoremap <silent> d :YRDeleteRange 'v'
nmap ds <Plug>Dsurround
nmap gx <Plug>NetrwBrowseX
nnoremap <silent> gp :YRPaste 'gp'
nnoremap <silent> gP :YRPaste 'gP'
xmap gS <Plug>VgSurround
nmap gcu <Plug>Commentary<Plug>Commentary
nmap gcc <Plug>CommentaryLine
omap gc <Plug>Commentary
nmap gc <Plug>Commentary
xmap gc <Plug>Commentary
nnoremap gf :call GotoFile("")
nmap j gj
vmap j gj
nmap k gk
vmap k gk
xnoremap <silent> p :YRPaste 'p', 'v'
nnoremap <silent> p :YRPaste 'p'
xnoremap <silent> x :YRDeleteRange 'v'
xnoremap <silent> y :YRYankRange 'v'
nmap ySS <Plug>YSsurround
nmap ySs <Plug>YSsurround
nmap yss <Plug>Yssurround
nmap yS <Plug>YSurround
nmap ys <Plug>Ysurround
map <F4> :e %:p:s,.h$,.X123X,:s,.c$,.h,:s,.X123X$,.c,
smap <S-Tab> <Plug>snipMateBack
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetrwBrowseX(expand("<cWORD>"),0)
nnoremap <silent> <SNR>77_yrrecord :call YRRecord3()
xnoremap <silent> <Plug>NERDCommenterUncomment :call NERDComment("x", "Uncomment")
nnoremap <silent> <Plug>NERDCommenterUncomment :call NERDComment("n", "Uncomment")
xnoremap <silent> <Plug>NERDCommenterAlignBoth :call NERDComment("x", "AlignBoth")
nnoremap <silent> <Plug>NERDCommenterAlignBoth :call NERDComment("n", "AlignBoth")
xnoremap <silent> <Plug>NERDCommenterAlignLeft :call NERDComment("x", "AlignLeft")
nnoremap <silent> <Plug>NERDCommenterAlignLeft :call NERDComment("n", "AlignLeft")
nnoremap <silent> <Plug>NERDCommenterAppend :call NERDComment("n", "Append")
xnoremap <silent> <Plug>NERDCommenterYank :call NERDComment("x", "Yank")
nnoremap <silent> <Plug>NERDCommenterYank :call NERDComment("n", "Yank")
xnoremap <silent> <Plug>NERDCommenterSexy :call NERDComment("x", "Sexy")
nnoremap <silent> <Plug>NERDCommenterSexy :call NERDComment("n", "Sexy")
xnoremap <silent> <Plug>NERDCommenterInvert :call NERDComment("x", "Invert")
nnoremap <silent> <Plug>NERDCommenterInvert :call NERDComment("n", "Invert")
nnoremap <silent> <Plug>NERDCommenterToEOL :call NERDComment("n", "ToEOL")
xnoremap <silent> <Plug>NERDCommenterNested :call NERDComment("x", "Nested")
nnoremap <silent> <Plug>NERDCommenterNested :call NERDComment("n", "Nested")
xnoremap <silent> <Plug>NERDCommenterMinimal :call NERDComment("x", "Minimal")
nnoremap <silent> <Plug>NERDCommenterMinimal :call NERDComment("n", "Minimal")
xnoremap <silent> <Plug>NERDCommenterToggle :call NERDComment("x", "Toggle")
nnoremap <silent> <Plug>NERDCommenterToggle :call NERDComment("n", "Toggle")
xnoremap <silent> <Plug>NERDCommenterComment :call NERDComment("x", "Comment")
nnoremap <silent> <Plug>NERDCommenterComment :call NERDComment("n", "Comment")
nnoremap <silent> <Plug>SurroundRepeat .
snoremap <silent> <Plug>snipMateBack a=snipMate#BackwardsSnippet()
snoremap <silent> <Plug>snipMateNextOrTrigger a=snipMate#TriggerSnippet()
xnoremap <silent> <Plug>(expand_region_shrink) :call expand_region#next('v', '-')
xnoremap <silent> <Plug>(expand_region_expand) :call expand_region#next('v', '+')
nnoremap <silent> <Plug>(expand_region_expand) :call expand_region#next('n', '+')
nmap <silent> <Plug>CommentaryUndo <Plug>Commentary<Plug>Commentary
imap S <Plug>ISurround
imap s <Plug>Isurround
imap 	 <Plug>snipMateNextOrTrigger
imap 	 <Plug>snipMateShow
imap  <Plug>Isurround
imap jj 
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set autoread
set backspace=eol,start,indent
set comments=sl:/*,mb:\ *,elx:\ */
set expandtab
set fileencodings=ucs-bom,utf-8,default,latin1
set helplang=en
set hidden
set hlsearch
set ignorecase
set incsearch
set isfname=@,48-57,/,.,-,_,+,,,#,$,%,~,=,:
set laststatus=2
set printoptions=paper:letter
set ruler
set runtimepath=~/dotfiles/vim_runtime/sources_non_forked/ack.vim,~/dotfiles/vim_runtime/sources_non_forked/bufexplorer,~/dotfiles/vim_runtime/sources_non_forked/ctrlp.vim,~/dotfiles/vim_runtime/sources_non_forked/goyo.vim,~/dotfiles/vim_runtime/sources_non_forked/mayansmoke,~/dotfiles/vim_runtime/sources_non_forked/nerdtree,~/dotfiles/vim_runtime/sources_non_forked/nginx.vim,~/dotfiles/vim_runtime/sources_non_forked/open_file_under_cursor.vim,~/dotfiles/vim_runtime/sources_non_forked/snipmate-snippets,~/dotfiles/vim_runtime/sources_non_forked/syntastic,~/dotfiles/vim_runtime/sources_non_forked/taglist.vim,~/dotfiles/vim_runtime/sources_non_forked/tlib,~/dotfiles/vim_runtime/sources_non_forked/vim-addon-mw-utils,~/dotfiles/vim_runtime/sources_non_forked/vim-airline,~/dotfiles/vim_runtime/sources_non_forked/vim-bundle-mako,~/dotfiles/vim_runtime/sources_non_forked/vim-coffee-script,~/dotfiles/vim_runtime/sources_non_forked/vim-colors-solarized,~/dotfiles/vim_runtime/sources_non_forked/vim-commentary,~/dotfiles/vim_runtime/sources_non_forked/vim-expand-region,~/dotfiles/vim_runtime/sources_non_forked/vim-fugitive,~/dotfiles/vim_runtime/sources_non_forked/vim-golang,~/dotfiles/vim_runtime/sources_non_forked/vim-indent-object,~/dotfiles/vim_runtime/sources_non_forked/vim-less,~/dotfiles/vim_runtime/sources_non_forked/vim-markdown,~/dotfiles/vim_runtime/sources_non_forked/vim-multiple-cursors,~/dotfiles/vim_runtime/sources_non_forked/vim-pyte,~/dotfiles/vim_runtime/sources_non_forked/vim-repeat,~/dotfiles/vim_runtime/sources_non_forked/vim-snipmate,~/dotfiles/vim_runtime/sources_non_forked/vim-snippets,~/dotfiles/vim_runtime/sources_non_forked/vim-surround,~/dotfiles/vim_runtime/sources_non_forked/vim-zenroom2,~/dotfiles/vim_runtime/sources/haskellmode-vim,~/dotfiles/vim_runtime/sources/jellybeans,~/dotfiles/vim_runtime/sources/nerdcommenter,~/dotfiles/vim_runtime/sources/peachpuff,~/dotfiles/vim_runtime/sources/peaksea,~/dotfiles/vim_runtime/sources/vim-clojure-static,~/dotfiles/vim_runtime/sources/vim-slime,~/dotfiles/vim_runtime/sources/vimux,~/dotfiles/vim_runtime/sources/yankring,~/.vim,/var/lib/vim/addons,/usr/share/vim/vimfiles,/usr/share/vim/vim74,/usr/share/vim/vimfiles/after,/var/lib/vim/addons/after,~/.vim/after,~/dotfiles/vim_runtime,~/dotfiles/vim_runtime/sources_non_forked/vim-snipmate/after,~/dotfiles/vim_runtime/sources_non_forked/vim-less/after,~/dotfiles/vim_runtime/sources_non_forked/vim-coffee-script/after
set shiftwidth=4
set showmatch
set showtabline=2
set smartcase
set smartindent
set smarttab
set statusline=\ %{HasPaste()}%F%m%r%h\ %w\ \ CWD:\ %r%{getcwd()}%h\ \ \ Line:\ %l
set suffixes=.bak,~,.swp,.o,.info,.aux,.log,.dvi,.bbl,.blg,.brf,.cb,.ind,.idx,.ilg,.inx,.out,.toc
set noswapfile
set tabline=%!airline#extensions#tabline#get()
set tabstop=4
set textwidth=120
set nowritebackup
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/SpiderOak\ Hive/all_notes/winter/systems/hash_it_out/c_code
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +1 main.c
badd +1 cache.c
badd +1 cache.h
args main.c cache.c cache.h
edit cache.c
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
edit cache.c
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal nobinary
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal cindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t,i
setlocal concealcursor=
setlocal conceallevel=0
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
setlocal nocursorcolumn
set cursorline
setlocal cursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal expandtab
if &filetype != 'c'
setlocal filetype=c
endif
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
set foldmethod=syntax
setlocal foldmethod=syntax
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=0
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
setlocal nolinebreak
setlocal nolisp
setlocal nolist
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal nomodeline
setlocal modifiable
setlocal nrformats=octal,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
setlocal norelativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=4
setlocal noshortname
setlocal smartindent
setlocal softtabstop=0
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=%!airline#statusline(1)
setlocal suffixesadd=
setlocal noswapfile
setlocal synmaxcol=3000
if &syntax != 'c'
setlocal syntax=c
endif
setlocal tabstop=4
setlocal tags=
setlocal textwidth=0
setlocal thesaurus=
setlocal noundofile
setlocal nowinfixheight
setlocal nowinfixwidth
setlocal wrap
setlocal wrapmargin=0
let s:l = 1 - ((0 * winheight(0) + 25) / 51)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
tabnext 1
if exists('s:wipebuf')
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToO
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
