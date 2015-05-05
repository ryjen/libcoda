require 'formula'

class Libarg3json < Formula
  homepage 'http://github.com/c0der78/arg3json'
  url 'https://github.com/c0der78/arg3json.git'
  sha1 '48e5da12f943929f05dc4a39c8f6ace76d8c44a0'

  def install
    ENV.universal_binary
    
    system "./configure", "--prefix=#{prefix}"
    ENV.deparallelize
    system "make install"
  end
end

