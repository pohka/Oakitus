find . -not -path './include*'  -not -path './projects/testgame/*' -not -path './engine/oak/core/stb_image.h' -a \( -name '*.cpp' -o -name '*.h' \) | xargs wc -l
read -p "Press enter to continue..."
