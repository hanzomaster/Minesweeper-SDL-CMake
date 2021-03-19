# Game Minesweeper

Trần Tuấn Thịnh - 20020265

## Cách cài đặt game

Trước khi download file zip về cần có [Visual Studio Build Tool 2019](https://visualstudio.microsoft.com/downloads/), [CMake](https://cmake.org/download/) và text editor [VScode](https://code.visualstudio.com/download)![Ảnh của Build Tool cần download](https://i.imgur.com/8RCTWm5.png)

1. Cài extension CMake ![Hình ảnh extension trong VScode](https://i.imgur.com/IVZ5Fh7.png)
2. Nhấn nút build của extension ![Ví dụ vị trí nút build](https://i.imgur.com/KfCrBhu.png)Nếu VScode yêu cầu chọn kit thì hãy chọn 'Visual Studio Build Tools 2019 Release - x86'. Nếu chương trình báo lỗi, hãy xoá sạch các file trong thư mục build và nhấn build lại. Nếu không thấy extension CMake hãy nhấn tổ hợp phím Ctrl+Shift+P và chọn CMake:Configure
3. Nhấn nút run![Ví dụ vị trí nút run](https://i.imgur.com/rZ1tMpo.png)và nếu không có lỗi gì tức là chương trình chạy thành công :+1:

## Các tính năng và luật chơi

- Luật chơi dò mìn truyền thống với 2 chế độ chơi Easy (9x9 và 10 mìn) hoặc Medium (13x13 và 25 mìn)
- Các quả mìn được rải ngẫu nhiên sau mỗi lần chơi
- Click chuột trái để mở một ô, chuột phải để đặt cờ báo hiệu mìn hoặc để mở các ô xung quanh khi đã đoán đúng vị trí mìn
- Khi bạn thắng hoặc thua, hãy nhấn nút 's' trên bàn phím để chơi lại chế độ đã chọn hoặc nút 'esc' để thoát về menu
