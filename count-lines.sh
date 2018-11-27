find . -not -path './include*'  -not -path './testgame/*' -not -path './oak/core/stb_image.h' -a \( -name '*.cpp' -o -name '*.h' \) | xargs wc -l
read -p "Press enter to continue..."
