1. Cài đặt và sử dụng:
Sử dụng lệnh git clone để clone game về máy

Ở terminal 
Nhập lệnh: <make> để dịch lại toàn bộ game
Nhập lệnh: <.\Game.exe> để bắt đầu trò chơi

2. Mô tả:
Ở phần menu:
Ấn chuột trái để vào chơi.

Trong trò chơi:
Chúng ta điều khiển nhân vật di chuyển và bắn các xe tăng, khi hạ được xe tăng ta sẽ nhận được điểm.
Đi lên ta ấn phím <W>.
Đi sang phải ta ấn phím <D>.
Đi sang trái ta ấn phím <A>.
Đi xuống dưới ta ấn phím <S>.
Để khai hoả súng ta ấn chuột trái, lăn con lăn chuột sẽ chuyển đổi giữa các vũ khí với nhau.
Các vũ khí sẽ không khai hoả được khi số đạn còn lại ở 0, đối với pistol khi hết đạn click chuột phải sẽ reload đạn.
Khi giết chết quái sẽ rơi ra các bao đạn và máu, đi vào sẽ được nạp đạn theo từng loại và hồi máu.
Ngẫu nhiên sẽ có các điểm thưởng trên bản đồ, khi đi vào ta sẽ được nhận điểm ngẫu nhiên.
Màn chơi sẽ kết thúc khi số máu nhân vật trở về 0, khi điểm số hiện tại cao hơn điểm số trong lịch sử điểm ta sẽ được ghi danh.

( link youtube : )

3. Kĩ thuật lập trình:
(*)sử dụng thư viện SDL.h, render ảnh theo lớp, nhân vật bằng thư viện SDL_image, load audio bằng thư viện SDL_Mixer.

(*)làm cho nhân vật chuyển động dựa trên toạ độ và góc xoay camera.

(*)chia chương trình thành nhiều file con nhỏ để mỗi file có một chức năng riêng thuận tiện cho việc lập trình và sửa lỗi.

(*)sử dụng các danh sách liên kết đơn để lưu danh sách quái, vật phẩm và hiệu ứng.

(*)bắt frame per second.

4. Kết luận và hướng phát triển:
đây mới chỉ là một trò chơi chưa hoàn chỉnh:
dự định phát triển trong tương lai sẽ có thêm nhiều màn chơi, phát triển thêm các loại boss, thêm các loại vật cản trong map, quái di chuyển phức tạp hơn là chỉ đi về phía người chơi như hiện tại, tối ưu hoá về mặt dung lượng và bộ nhớ giúp tốn ít không gian lưu trữ và game chạy được mượt mà hơn.

(NGUỒN THAM KHẢO: https://www.parallelrealities.co.uk/tutorials/bad/bad1.php, một vài lỗi nhỏ được tra cứu trên stackoverflow,...).