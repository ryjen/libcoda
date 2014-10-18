require 'formula'

class Arg3 < Formula
  homepage 'http://github.com/c0der78/libarg3'
  url 'https://github.com/c0der78/libarg3.git'
  sha1 '6177abcc886d9d16190d2ce449d1c18897c56d04'

  head 'http://github.com/c0der78/libarg3.git'
	
  version '0.5'
	
  devel do
    url 'file:///Users/Ryan/Devel/libarg3/arg3-0.5.tar.gz'
  end

  def install
    ENV.universal_binary
    
    system "./configure", "--prefix=#{prefix}"
    ENV.deparallelize
    system "make install"
  end
end
