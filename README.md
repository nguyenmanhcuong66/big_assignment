# Flappy Bird ++

## Giới thiệu

Flappy Bird ++ là phiên bản mở rộng của game Flappy Bird cổ điển, được lập trình bằng C++ sử dụng thư viện SDL2. Game giữ nguyên lối chơi nhảy qua các ống nước nhưng có thêm các tính năng mới như mạng sống, vật phẩm hồi mạng, tăng tốc di chuyển và hệ thống điểm số với mức độ khó tăng dần.

---

## Hướng dẫn chơi

* **Mục tiêu:** Điều khiển chú chim bay qua các ống nước mà không bị va chạm để tích điểm.
* Chim có 3 mạng (lives). Khi va chạm với ống, mất một mạng, game kết thúc khi hết mạng hoặc khi chim rơi ra khỏi màn hình.
* Sau mỗi level , tốc độ ống tăng lên giúp thử thách hơn. Ngoài ra cơ chế dịch chuyển ống ngẫu nhiên làm tăng thêm phần kịch tính cho game.
* **Vật phẩm hồi mạng** xuất hiện ngẫu nhiên, khi ăn được sẽ tăng thêm mạng sống. Người chơi có thể tối ưu thu thập vật phẩm bằng cơ chế tăng tốc của chim - "chế độ săn mồi".
* Cơ chế bất tử sau khi va chạm trong thời gian 1s giúp người chơi thoải mái hơn trong những tình huống xử lí phức tạp yêu cầu tốc độ cao.
* Các thao tác như nhảy cao hay rơi nhanh ,tăng tốc giúp người chơi khai phá tối đa khả năng xử lí tình huống ,phản xạ.

### Phím điều khiển:

| Phím  | Tác dụng                     |
| ----- | ---------------------------- |
| SPACE | Chim nhảy lên                |
| I     | Chim nhảy lên mạnh hơn       |
| J     | Chim rơi nhanh xuống         |
| SHIFT | Tăng tốc di chuyển sang phải |
| Q     | Thoát game và hiển thị điểm  |

---

## Hướng dẫn cài đặt

### Yêu cầu

* Máy tính đã cài đặt:

  * **C++ compiler** (g++ hoặc clang) hỗ trợ C++11 trở lên.
  * **SDL2**, **SDL2\_image**, **SDL2\_ttf** đã được cài đặt và cấu hình đúng.

### Cách build và chạy

1. Clone hoặc tải project về máy:

```bash
git clone https://github.com/username/flappy-bird-plus.git
cd flappy-bird-plus
```
2. Đảm bảo thư mục assets/ có đầy đủ các file:

*background.png

*bird.png

*pipe.png

*item.png

*arial.ttf

3. Biên dịch project (ví dụ với g++):

g++ main.cpp -o flappybird -lSDL2 -lSDL2_image -lSDL2_ttf

4. Chạy game:
./flappybird
## Cập nhật và tính năng tương lai
Phiên bản hiện tại có các tính năng:

*Chim có mạng sống.

*Vật phẩm hồi mạng xuất hiện ngẫu nhiên mỗi 10 giây.

*Tốc độ ống tăng theo điểm.

*Các phím điều khiển bổ sung giúp tăng trải nghiệm.
## Hướng phát triển game

*Thêm âm thanh hiệu ứng khi chim nhảy, ăn vật phẩm, va chạm.

*Tối ưu hiệu suất và fix lỗi.

*Thêm giao diện menu bắt đầu và màn hình kết thúc game.

*Lưu và hiển thị điểm cao nhất (high score).

*Thêm nhiều loại vật phẩm với hiệu ứng khác nhau (tăng tốc, giảm tốc, mạng thêm...).

*Thiết kế lại đồ họa đẹp mắt hơn hoặc tạo hiệu ứng chuyển động mượt mà.

*Hỗ trợ đa nền tảng (Windows, Linux, MacOS).
## Nguồn tham khảo
*SDL2 official documentation

*Lazy Foo' Productions SDL2 tutorials

*Các bài viết và tài liệu về lập trình game 2D với SDL2

*Code mẫu Flappy Bird trên GitHub và các nguồn mở
*Tham khảo, học hỏi từ kênh youtube "Mike Shah" với series "SDL2 Simple Directmedia Layer":https://www.youtube.com/watch?v=QM4WW8hcsPU&list=PLvv0ScY6vfd-p1gSnbQhY7vMe2rng0IL0

## Sinh viên 
Tên : Nguyễn Mạnh Cường
Mã sinh viên: 24021398

