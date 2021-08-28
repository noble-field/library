# ls Color for Linux
eval `dircolors ~/.dircolors`
alias ls='ls --color=auto'

# ls Color for Mac
# export CLICOLOR=1
# export LSCOLORS="GxFxCxDxBxegedabagaced"

# Prompt Script
source ~/.bash_prompt.sh

# aliases for competitive programming
alias test='./a.out<in'

function ctest {
	g++ $1
	test
}

function cclip {
	cat $1 | clip
}

function g++o {
	g++ -o $1 $1.cpp
}

# ac-library
export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:$HOME/ac-library

[ -f ~/.fzf.bash ] && source ~/.fzf.bash

# fzf
export FZF_DEFAULT_OPTS="--height 50% --layout=reverse --border --inline-info --preview 'head -100 {}'"
