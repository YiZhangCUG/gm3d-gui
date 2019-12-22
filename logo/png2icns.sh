#/bin/bash

png_file=${1}
icns_name=${2}

mkdir ${icns_name}".iconset"

sips -z 16 16 ${png_file} --out ${icns_name}.iconset/icon_16x16.png
sips -z 32 32 ${png_file} --out ${icns_name}.iconset/icon_16x16@2x.png
sips -z 32 32 ${png_file} --out ${icns_name}.iconset/icon_32x32.png
sips -z 64 64 ${png_file} --out ${icns_name}.iconset/icon_32x32@2x.png
sips -z 64 64 ${png_file} --out ${icns_name}.iconset/icon_64x64.png
sips -z 128 128 ${png_file} --out ${icns_name}.iconset/icon_64x64@2x.png
sips -z 128 128 ${png_file} --out ${icns_name}.iconset/icon_128x128.png
sips -z 256 256 ${png_file} --out ${icns_name}.iconset/icon_128x128@2x.png
sips -z 256 256 ${png_file} --out ${icns_name}.iconset/icon_256x256.png
sips -z 512 512 ${png_file} --out ${icns_name}.iconset/icon_256x256@2x.png
sips -z 512 512 ${png_file} --out ${icns_name}.iconset/icon_512x512.png
sips -z 1024 1024 ${png_file} --out ${icns_name}.iconset/icon_512x512@2x.png

iconutil -c icns ${icns_name}.iconset