require 'formula'

class Arg3 < Formula
  homepage 'http://github.com/c0der78/libarg3'
  url 'https://github.com/c0der78/libarg3.git'
  sha1 '6177abcc886d9d16190d2ce449d1c18897c56d04'

  depends_on 'premake' => :build

  devel do
    url 'file:///Users/c0der78/Devel/cpp/arg3/libarg3_0.1.tar.gz'
    #sha1 '5e39ea448ca2db9e1ed1fa4765e3138e74d77083'
  end

  def install
    system "premake4", "--shared", "gmake"

    ENV["config"] = "release"

    system "make"

    system "premake4", "install", prefix
  end
end
