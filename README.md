# OSTACLE RACE GAME

## Giới thiệu
 - Họ và tên :Trần Thuận Vy
 - MSSV      : 23020717
 - Lớp       : K68J
 
 
OSTACLE RACE GAME trò chơi được lấy dựa nên từ tựa game Dino kinh điển trên Google,đồng thời đã được phát triển thêm một số tính năng .Bạn hãy cố gắng hết sức để tránh các vật cản và giành chiến thắng 
## 0.Cách tải game 
 - Tải game được nén tại link sau:
  
  
## 1.Bắt đầu game & Kết thúc game
 - Ấn nút Play Game để bắt đầu chơi game
 - Nếu bạn chưa muốn chơi game  thì click chuột vào nút Exit, cửa sổ sẽ lập tức đóng lại.
  ![image](https://hackmd.io/_uploads/S1y1w6uWA.png)
  
 - Ấn nút Play Again để chơi lại hoặc ấn nút EXIT để thoát khỏi game 
 [![image](https://hackmd.io/_uploads/By4ev7Y-A.png)
](https://i.imgur.com/Cnle9f9.png)

## 2.Các thành phần trong game 
  - Nhân vật game chính  và đạn bắn của nhân vật

  [![image](https://hackmd.io/_uploads/rkPEBZKW0.png)](https://i.imgur.com/Cnle9f9.png)      [![image](https://hackmd.io/_uploads/rJV3SZYW0.png)
](https://i.imgur.com/Cnle9f9.png)
  
  - Đối tượng hiểm họa và đạn bắn của đối tượng 
  - [![image](https://hackmd.io/_uploads/r109PZtWR.png)](https://i.imgur.com/Cnle9f9.png) [![image](https://hackmd.io/_uploads/rJOPcbKWA.png)
](https://i.imgur.com/Cnle9f9.png)
  
  - Vật cản
  [![image](https://hackmd.io/_uploads/rkPF5bFbR.png)
](https://i.imgur.com/Cnle9f9.png)
  
## 3.Cách chơi
 ### Bạn sẽ điều khiển đối tượng game chính để vượt chướng ngại vật bằng cách:
 
 -[![image](https://hackmd.io/_uploads/rk7Q8XtbR.png)](https://i.imgur.com/Cnle9f9.png)
 Click chuột trái để nhân vật bắt đầu di chuyển và Click chuột phải để nhât vật game chính bắn ra đan để tiêu diệt nhân vật đe dọa  
 
 -[![image](https://hackmd.io/_uploads/H1swHXKW0.png)](https://i.imgur.com/Cnle9f9.png)  
 Là các nút di chuyển lên , xuống cho game 
    
## 4.Chiến thắng và thất bại
   - Bạn sẽ chiến thắng nếu vượt hết chướng ngại vật mà, không bị tiêu diệt bởi đối tượng đe dọa và đi hết quãng đường 
   [![image](https://hackmd.io/_uploads/H16KFhubR.png)
](https://i.imgur.com/Cnle9f9.png)
   
   - Bạn sẽ thất bại nếu bị đạn của nhân vật đe dọa bắn trúng hoặc chạm vào vật vản trên đường đi 
   [![image](https://hackmd.io/_uploads/B1Bzm3ubA.png)
](https://i.imgur.com/Cnle9f9.png)
[](https://i.imgur.com/Cnle9f9.png) 
[:link:][GitHub-Sync]​ Về đồ họa của game và âm thanh
   - Các hình ảnh, đồ họa , âm thanh đều được lấy về từ trên Google
   
[:link:][GitHub-Sync] Về source code game 
  - CommonFunc: chứa các thư viện SDL,..và các biến tĩnh  sử dụng cho mọi chỗ trong code
     CheckCollision: kiểm tra va chạm giữa các vật trong game
  - BaseObject : là lớp đại diện cho một đối tượng cơ bản trong trò chơi, tức là các lớp đối tượng khác sẽ kế thừa lại những tính chất cơ bản của lớp này .
    LoadImg : Tải hình ảnh và tạo texture cho game
    SetRect : Thiết lập vị trí cho đối tượng
    SDL_Rect GetRect():Lấy vị trí của đối tượng
    SDL_Texture* GetObject: Lấy con trỏ đến texture của đối tượng
    void RenderTexture: Vẽ texture lên renderer
    void Free(): giải phóng texture
- MainObject : là lớp đại diện cho nhân vật game chính , được kế thừa những tính chất cơ bản có sẵn  của lớp BaseObject kia và các tính năng riêng của lớp 
    HandleInputAction: Xử lí sự kiện từ chuột + bàn phím
    DoPlayer : Xử lý di chuyển của nhân vật 
    Mapwhenrunner: Hàm xử lý hiện map khi nhân vật di chuyển 
    CheckToMap : Hàm kiểm tra giữa nhân vật game với title map 
    CheckToWin : Kiểm tra nhân vật đã thắng hay chưa 

- BulletObject: là lớp đại diện cho đạn bán ra của nhân vật game chính và nhân vật đe dọa ,được kế thừa những tính chất cơ bản có sẵn  của lớp BaseObject kia và các tính năng riêng của lớp
    LoadImgBullet :Load ảnh đạn
    HandleMove : Hàm quản lý việc di chuyển của một đối tượng đạn trong ranh giới ngang được chỉ định

- ThreatObject: là lớp đối tượng hiểm họa cũng được kế thừa từ BaseObject
- Explosion : là lớp đối tượng khởi tạo và xử lý đạn bắn cho các đối tượng  
- Menu và GameOver :tại lên cửa số màn hình Play Game và Play Again  
- GameMap : tải map di chuyển cho nhân vật
- Timer : Xử lý thời gian ,FPS 
- TextObject : là lớp xử lý kỹ thuật hiện chữ trên màn hình 
- main:tổng hợp mọi thứ để thiết lập và chạy được game.

[:link:][GitHub-Sync] Các kỹ thuật lập trình đã sử dụng 
- Tính kế thừa trong class
- Xử lý va chạm giữa các đối tượng trong trò chơi 
- Sử dụng vector, con trỏ 
- Sử dụng kỹ thuật title map
- Chia file cho dễ quản lý 
- Biến (static, extern), vòng lặp, cấu trúc rẽ nhánh, mảng, chuỗi.
- Con trỏ, map, vector

[:link:][GitHub-Sync] Các nguồn tham khảo 
- Lazyfoo.net
- <https://phattrienphanmem123az.com/>

[:link:][GitHub-Sync] Việc hoàn thiện 1 dự án lập trình như thế này giúp em mở mang kiến thức rất nhiều:
- Hiểu được mô hình phát triển 1 phần mềm kiểu thác nước: Phân tích, thiết kế, lập trình, kiểm thử, chuyển giao và bảo trì (forever).
- Biết cách chia nhỏ file + class để dễ quản lý dự án hơn.
- Cách dùng github.
- Hiểu sơ sơ một số khía cạnh của lập trình hướng đối tượng: kế thừa, đa hình,...
- Học được cách sử dụng C++ và SDL2 để tạo được một game cơ bản cho bản thân.


 
