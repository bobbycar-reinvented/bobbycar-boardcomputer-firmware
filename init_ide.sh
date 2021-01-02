#!/bin/sh

platformio init --ide qtcreator

echo "CONFIG+=c++17" >> platformio.pro

echo "OTHER_FILES += \\" >> platformio.pro

#for i in $(find data -type f)
#do
#    echo "    $i \\" >> platformio.pro
#done

echo "    partitions_16M_ota.csv \\" >> platformio.pro
echo "    partitions_4M_noota.csv \\" >> platformio.pro
echo "    partitions_4M_ota.csv \\" >> platformio.pro
echo "    LICENSE" >> platformio.pro
echo "    README.md" >> platformio.pro
