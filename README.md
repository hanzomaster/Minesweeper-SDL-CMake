# Game Minesweeper

Trần Tuấn Thịnh - 20020265

Bài tập lớn của lớp lập trình nâng cao 2021II_INT2215_2

## Cách cài đặt game

- Trước khi cài đặt cần có [Visual Studio Build Tool 2019](https://visualstudio.microsoft.com/downloads/)![Ảnh của Build Tool cần download](https://i.imgur.com/8RCTWm5.png) Build system [CMake](https://cmake.org/download/) và text editor [VSCode](https://code.visualstudio.com/download) kèm theo extension [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake) ![Ảnh của extension](https://i.imgur.com/493rLnD.png) và [CMake Tool](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) ![Ảnh của extension](https://i.imgur.com/onhYCHX.png)
- Tải game ở [đây](https://github.com/hanzomaster/Minesweeper-SDL-CMake), nhấn vào mục Code và chọn Download Zip![Ảnh minh hoạ phần download](https://i.imgur.com/mbLOBYv.png)
- Sau khi đã tải về và giải nén xong hãy thêm đường dẫn đến mục SDL2/lib/x64 vào PATH của máy tính
- Tiếp theo hãy mở app CMake (cmake-gui), chọn mục Browse Code và chỉ tới đường dẫn đến file project và file build. Sau đó nhấn Configure (nếu có bất kì thông báo nào hiện lên hãy nhấn OK) và cuối cùng nhấn Generate
- Mở file game trên VSCode và ở thanh Status Bar nó có thể sẽ trông như này ![Ví dụ vị trí nút build](https://i.imgur.com/KfCrBhu.png)Nếu VScode yêu cầu chọn kit thì hãy chọn 'Visual Studio Build Tools 2019 Release - amd64' Nếu không thấy extension CMake ở Status Bar hãy nhấn tổ hợp phím Ctrl+Shift+P và chọn CMake:Configure
- Nếu VSCode báo thành công thì lúc này file game của chúng ta đã ở trong mục build/Debug dưới dạng đuôi .exe

Video hướng dẫn tại [đây](https://youtu.be/kNo-UdmJrmU)

## Các tính năng và luật chơi

- Luật chơi dò mìn truyền thống với 2 chế độ chơi:
  - Easy (9x9 và 10 ô mìn)
  - Medium (16x16 40 ô mìn)
- Các quả mìn được rải ngẫu nhiên sau mỗi lần chơi
- Click chuột trái để mở một ô, chuột phải để đặt cờ báo hiệu mìn và chuột giữa để mở các ô xung quanh khi đã đoán đúng vị trí mìn
- Khi bạn thắng hoặc thua, hãy nhấn nút 's' trên bàn phím để chơi lại chế độ đã chọn hoặc nút 'esc' để thoát về menu

###### tags: `Minesweeper` `C++` `SDL2`
