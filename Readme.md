## 1. Cài đặt và sử dụng:
Sử dụng lệnh git clone để clone game về máy.

Ở terminal 
Dịch chương trình
```
make
```
hoặc 
```
g++ -Iinclude -Iinclude/SDL2 -Iinclude/Headers -Llib -o Game src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
```
Chạy chương trình
```
.\Game.exe
```
hoặc 
```
make run 
```
để dịch và chạy chương trình.

## 2. Mô tả:
Ở phần menu:
- Ấn chuột trái để vào chơi.

Trong trò chơi:

- Chúng ta điều khiển nhân vật di chuyển và bắn các xe tăng, khi hạ được xe tăng ta sẽ nhận được điểm.

- Di chuyển lên nhấn W

- Di chuyển sang phải nhấn D.

- Di chuyển sang trái nhấn A.

- Di chuyển xuống nhấn S.

- Để khai hoả súng ta ấn chuột trái, lăn con lăn chuột sẽ chuyển đổi giữa các vũ khí với nhau.

- Các vũ khí sẽ không khai hoả được khi số đạn còn lại ở 0, đối với pistol khi hết đạn click chuột phải sẽ reload đạn.

- Khi giết chết quái sẽ rơi ra các bao đạn và máu, đi vào sẽ được nạp đạn theo từng loại và hồi máu.

- Ngẫu nhiên sẽ có các điểm thưởng trên bản đồ, khi đi vào ta sẽ được nhận điểm ngẫu nhiên.

- Màn chơi sẽ kết thúc khi số máu nhân vật trở về 0, khi điểm số hiện tại cao hơn điểm số trong lịch sử điểm ta sẽ được ghi danh. Sau khi ghi danh bấm Enter để trở lại màn hình chính.

( link youtube : https://www.youtube.com/watch?v=7G8WVOmEgXA)

## 3. Kết luận và hướng phát triển:
Đây mới chỉ là một trò chơi chưa hoàn chỉnh:
dự định phát triển trong tương lai sẽ có thêm nhiều màn chơi, phát triển thêm các loại boss, thêm các loại vật cản trong map, quái di chuyển phức tạp hơn là chỉ đi về phía người chơi như hiện tại, tối ưu hoá về mặt dung lượng và bộ nhớ giúp tốn ít không gian lưu trữ và game chạy được mượt mà hơn.

(NGUỒN THAM KHẢO: parallelrealities.co.uk, một vài lỗi nhỏ được tra cứu trên stackoverflow,...).


Phân công công việc nhóm:
Ngô Thượng Hiếu: làm quái, đạn quái, map, audio.
