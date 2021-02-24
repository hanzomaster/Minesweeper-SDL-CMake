# Game Minesweeper

## Bài tập lớn làm game Minesweeper với thư viện SDL (ngôn ngữ C++) và Visual Studio Code

_Trần Tuấn Thịnh - 20020265_

### Cách cài đặt và chơi game

1. Cần có text editor Visual Studio Code và extension CMake ![Screenshot 2021-02-23 220245](https://user-images.githubusercontent.com/49803999/108862526-e3ef2b80-7622-11eb-90bc-f7738601d9e9.png)
2. Thay đổi các đường dẫn trong file trong main.cpp (dòng 117, 133, 149 và 166) về đường dẫn **tuyệt đối** tương ứng.
3. Nhấn nút build của extension![Screenshot 2021-02-23 220715](https://user-images.githubusercontent.com/49803999/108863413-c53d6480-7623-11eb-9464-c0d297ecde6b.png). Nếu vscode yêu cầu chọn kit thì hãy chọn 'Visual Studio Build Tools 2019 Release - x86'. Nếu chương trình báo lỗi, hãy xoá sạch các file trong thư mục build và nhấn build lại.
4. Nhấn nút run![Screenshot 2021-02-23 221205](https://user-images.githubusercontent.com/49803999/108863918-48f75100-7624-11eb-935e-f1d6af420f10.png) và thưởng thức game nhé!

### Các tính năng và luật chơi

- Luật chơi dò mìn truyền thống với khu vực chơi 10x10 và 12 ô mìn
- Các quả bom được rải ngẫu nhiên sau mỗi lần chơi
- Click chuột trái để mở một ô, chuột phải để đặt cờ báo hiệu bom và chuột giữa để khám phá các ô xung quanh khi phát hiện bom
- Khi bạn thắng hoặc thua, hãy nhấn nút 's' trên bàn phím để chơi lại hoặc nút 'esc' để thoát
