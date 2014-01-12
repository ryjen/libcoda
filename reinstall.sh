make dist-gzip
cp arg3.rb /usr/local/Library/Formula
brew uninstall arg3; 
brew cleanup; 
brew install --devel arg3
