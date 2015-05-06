require 'formula'

class Libarg3 < Formula
  homepage 'http://github.com/c0der78/libarg3'
  url 'https://github.com/c0der78/libarg3/archive/0.5.1.tar.gz'
  sha1 '168aa6a1d06119d2e64b5bdfec82799c411dcfb5'

  head 'http://github.com/c0der78/libarg3.git'

  version '0.5.1'

  depends_on 'automake'
  depends_on 'autoconf'
  depends_on 'json-c'
  depends_on 'mysql'
  depends_on 'sqlite3'
  depends_on 'curl'
  depends_on 'uriparser'

  def install
    ENV.universal_binary
    system "./configure", "--prefix=#{prefix}"
    ENV.deparallelize
    system "make"
    system "make install"
  end
end
