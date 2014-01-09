cp arg3.rb /usr/local/Library/Formula
make dist-gzip
brew uninstall arg3; 
brew cleanup; 
brew install --devel arg3
