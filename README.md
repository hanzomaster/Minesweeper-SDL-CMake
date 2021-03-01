# Game Minesweeper

_Trần Tuấn Thịnh - 20020265_

## Cách cài đặt game

Trước khi download file zip về cần có Visual Studio Build Tool 2019, CMake và text editor VScode

- [Build Tool](https://visualstudio.microsoft.com/downloads/)![Ảnh của Build Tool cần download](https://i.imgur.com/8RCTWm5.png)

- [CMake](https://cmake.org/download/)
- [VScode](https://code.visualstudio.com/download)

1. Cài extension CMake ![Hình ảnh extension trong VScode](https://i.imgur.com/IVZ5Fh7.png)

2. Thay đổi các đường dẫn trong file trong main.cpp (dòng 117, 133, 149 và 166) về đường dẫn **tuyệt đối** tương ứng
3. Nhấn nút build của extension (nên tạo 1 thư mục build riêng trước khi nhấn nút build) ![Ví dụ vị trí nút build](https://i.imgur.com/KfCrBhu.png)Nếu VScode yêu cầu chọn kit thì hãy chọn 'Visual Studio Build Tools 2019 Release - x86'. Nếu chương trình báo lỗi, hãy xoá sạch các file trong thư mục build và nhấn build lại
4. Nhấn nút run![Ví dụ vị trí nút run](https://i.imgur.com/rZ1tMpo.png)và nếu không có lỗi gì tức là chương trình chạy thành công :+1:

## Các tính năng và luật chơi

- Luật chơi dò mìn truyền thống với khu vực chơi 10x10 và 12 ô mìn
- Các quả bom được rải ngẫu nhiên sau mỗi lần chơi
- Click chuột trái để mở một ô, chuột phải để đặt cờ báo hiệu bom và chuột giữa để khám phá các ô xung quanh khi phát hiện bom
- Khi bạn thắng hoặc thua, hãy nhấn nút 's' trên bàn phím để chơi lại hoặc nút 'esc' để thoát

#### tags: `SDL2` `C++` `Minesweeper`
