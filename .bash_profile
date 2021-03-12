export CLICOLOR=1
export LSCOLORS="GxFxCxDxBxegedabagaced"

export GOPATH=$HOME/go
export PYENV_ROOT=$HOME/.pyenv

export GOPRIVATE=github.com/Finatext/logger
export PATH=$PATH:$GOPATH/bin
export PATH=$PATH:$PYENV_ROOT/bin
eval "$(pyenv init -)"

if [ -f ~/.bashrc ] ; then
	. ~/.bashrc
fi
