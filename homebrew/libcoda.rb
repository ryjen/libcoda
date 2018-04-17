require 'formula'

class LibCoda < Formula
  homepage 'http://github.com/ryjen/libcoda'

  head 'http://github.com/ryjen/libcoda.git'

  version '0.5.1'

  depends_on 'cmake'
  depends_on 'json-c'
  depends_on 'mysql'
  depends_on 'sqlite3'
  depends_on 'curl'
  depends_on 'uriparser'

  def install
    ENV.universal_binary
    system "cmake", "-CMAKE_INSTALL_PREFIX=#{prefix}"
    ENV.deparallelize
    system "make"
    system "make install"
  end
end
