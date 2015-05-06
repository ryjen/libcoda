require 'formula'

class Libarg3 < Formula
  homepage 'http://github.com/c0der78/libarg3'
  url 'https://github.com/c0der78/libarg3/archive/0.5.1.tar.gz'
  sha1 '2cc85dfcc6f074d79ec33fc11d41a5bbcf34234b'

  head 'http://github.com/c0der78/libarg3.git'

  version '0.5.1'

  depends_on 'json-c'
  depends_on 'mysql'
  depends_on 'sqlite3'
  depends_on 'curl'
  depends_on 'uriparser'

  def install
    ENV.universal_binary
    system "./bootstrap.sh", "--prefix=#{prefix}"
    ENV.deparallelize
    system "make"
    system "make install"
  end
end
