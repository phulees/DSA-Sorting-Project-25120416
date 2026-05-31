# BÁO CÁO ĐỒ ÁN MÔN HỌC

* **Tên môn học:** Cấu trúc Dữ liệu và Giải thuật (Data Structures and Algorithms)
* **Thời gian học:** Học kỳ 2 - 2025/2026
* **Họ và tên sinh viên:** Lê Nguyễn Bá Phú
* **MSSV:** 25120416
* **Họ và tên sinh viên:** Lương Hồ Bảo Phúc
* **MSSV:** 25120418
* **Họ và tên sinh viên:** Lê Minh Triết
* **MSSV:** 25120456

---

## 1. Thuật toán cài đặt tốt nhất ở lần chạy đầu tiên

Ở lần nộp đầu tiên, mục tiêu ưu tiên là sự chính xác, tính ổn định và an toàn để lấy điểm cơ bản. 

* **Thuật toán sử dụng:** Merge Sort (Sắp xếp trộn) truyền thống cho cả 3 bài (`int`, `strlexi`, `strlenlexi`). Ở bài `strlenlexi`, Merge Sort kết hợp với hàm `isSmaller` tùy chỉnh để ưu tiên so sánh độ dài trước.
* **Phương thức tối ưu hóa:** 
  * Sử dụng `std::ios_base::sync_with_stdio(false);` và `cin.tie(NULL);` để vô hiệu hóa đồng bộ luồng I/O chuẩn của C++, giúp việc đọc/ghi $100.000$ dòng dữ liệu nhanh hơn đáng kể.
* **Lý do lựa chọn thuật toán này:** 
  * Merge Sort cung cấp độ phức tạp thời gian luôn ổn định ở mức $O(N \log N)$ trong mọi trường hợp (tốt nhất, trung bình, và xấu nhất). Tránh được rủi ro rơi vào trường hợp xấu nhất $O(N^2)$ như thuật toán Quick Sort khi chọn chốt (pivot) không hợp lý.
  * *Nhược điểm ở lần 1:* Tại mỗi bước `merge`, mã nguồn liên tục khởi tạo hai mảng con (`vector L`, `vector R` hoặc `left`, `right`) và sao chép dữ liệu (đặc biệt là sao chép chuỗi `std::string`). Điều này gây tốn chi phí bộ nhớ $O(N \log N)$ và chi phí cấp phát (allocation) rất lớn trên Heap.

---

## 2. Cách thức sinh Test Case (Mã nguồn: `test_gen.cpp`)

Công cụ `test_gen.cpp` cung cấp Command-line Interface theo chuẩn, sử dụng thư viện `<random>` (với `mt19937`) trong C++23 để sinh dữ liệu ngẫu nhiên phân bố đều. Bộ test này được thiết kế cố tình nhắm vào các điểm yếu của những thuật toán sắp xếp không được tối ưu hóa tốt (đặc biệt là Quick Sort cơ bản và Merge Sort cấp phát bộ nhớ kém).

### Bài `int` (Sắp xếp số nguyên, N = 100.000)
* **Test 1 (Mảng giảm dần):** Ép mảng ngược hoàn toàn từ $100.000$ về $1$. Bẫy thuật toán Quick Sort ngây thơ (chọn chốt ở đầu/cuối), khiến thời gian chạy thoái hóa thành $O(N^2)$.
* **Test 2 (Rừng vô tính):** $100.000$ số giống hệt nhau (-9999). Đánh sập Quick Sort nếu hàm phân hoạch (partition) chia mảng thành 2 phần mất cân bằng cực đại.
* **Test 3 (Bom bộ nhớ):** Nhồi các giá trị biên `INT_MAX`, `INT_MIN` và số âm xen kẽ. Nhằm gây lỗi Memory Limit Exceeded hoặc Segmentation Fault cho các thuật toán Counting/Radix Sort dùng mảng đếm kích thước tĩnh dựa trên dải giá trị.
* **Test 4 (Đội hình chữ V):** Nửa đầu giảm dần, nửa sau tăng dần. Tấn công chiến lược chọn chốt ở giữa (mid) của Quick Sort.
* **Test 5 (Hỗn loạn):** Dải số phân bố ngẫu nhiên toàn bộ trục `int`. Đo lường hiệu suất I/O và tốc độ chạy thực tế.

### Bài `strlexi` (Ưu tiên từ điển, N = 100.000)
* **Test 1 (100 chữ 'z'):** Các chuỗi hoàn toàn giống nhau. Ép các comparator phải duyệt qua $100$ ký tự ở mỗi phép so sánh.
* **Test 2 (Anh em sinh đôi):** Chuỗi có 99 ký tự đầu giống hệt nhau, chỉ khác ở ký tự cuối. Tối đa hóa thời gian so sánh từ điển ($O(L)$ cho mỗi phép toán). 
* **Test 3 (Ngược dòng thác):** Mảng ngẫu nhiên nhưng ép sắp xếp giảm dần. Ép lỗi thời gian thực thi (TLE) với Quick Sort mảng chuỗi.
* **Test 4 (Bẫy độ dài Out-of-bounds):** Xen kẽ chuỗi 10 ký tự và 100 ký tự chung tiền tố. Nhằm bắt lỗi các code tự viết vòng lặp `for` so sánh ký tự mà quên kiểm tra biên (`a.length()`).
* **Test 5 (Bãi rác bộ nhớ):** Độ dài (10-100) và ký tự hoàn toàn ngẫu nhiên. Trừng phạt các bài Merge Sort (giống thuật toán lần 1) liên tục cấp phát và sao chép chuỗi mới, làm tràn bộ nhớ Heap.

### Bài `strlenlexi` (Ưu tiên độ dài, N = 10.000)
* **Test 1 (Cú lừa từ điển giả):** Cặp `"apple"` đấu với `"aaaaaaaaaa"`. Tấn công các code viết sai logic: So sánh từ điển trước, độ dài sau.
* **Test 2 (Áp lực độ dài):** Chung 99 ký tự 'x' ở tiền tố. Bào mòn giới hạn thời gian (1 giây) của hệ thống với các thuật toán $O(N^2)$.
* **Test 3 (Thác nước ngược):** Chuỗi dài đứng trước, chữ cái lớn đứng trước. 
* **Test 4 (Bản sao vô tận):** $10.000$ chuỗi toàn chữ 'm'. Bẫy lỗi đệ quy quá sâu (Stack Overflow).
* **Test 5 (Bữa tiệc biên giới):** Tập trung sinh chuỗi dài biên đúng $10$ và $100$. Gây khó dễ cho Radix Sort sắp xếp chuỗi không đồng nhất.

---

## 3. Thuật toán cài đặt tốt nhất ở lần thứ hai

Từ những nhược điểm phát hiện được sau khi xây dựng bộ Test Case, lần nộp thứ hai tập trung giải quyết triệt để vấn đề "nút thắt cổ chai" liên quan đến **Cấp phát bộ nhớ (Memory Allocation)** và **Sao chép dữ liệu (Data Copying)**.

* **Đối với bài `int`:** 
  * Vẫn giữ thuật toán Merge Sort, nhưng thay vì khởi tạo `vector<int> L` và `R` bên trong hàm `merge`, tôi đã cấp phát sẵn một mảng tĩnh `vector<int> temp(n)` từ hàm `main` và truyền tham chiếu vào. Điều này giúp giảm độ phức tạp không gian phụ (extra space) trong các lời gọi đệ quy xuống $O(N)$ duy nhất, triệt tiêu hoàn toàn chi phí khởi tạo mảng động liên tục.
* **Đối với bài `strlexi`:** 
  * Thay vì sao chép chuỗi tốn kém (việc gán chuỗi dài 100 ký tự mất $O(L)$ thời gian), tôi chuyển sang **sắp xếp con trỏ chuỗi** (`vector<const string*> ptrs`). Khi đổi chỗ (swap) hoặc trộn (merge), chương trình chỉ thao tác trên địa chỉ bộ nhớ (chi phí $O(1)$) thay vì dữ liệu chuỗi thực tế. Mảng `temp` cũng được dùng chung tương tự bài `int`.
* **Đối với bài `strlenlexi`:** 
  * Áp dụng chiến lược **Hybrid Sorting (Bucket Sort + Merge Sort)**. Do độ dài chuỗi là hữu hạn (giả sử `maxLen` <= 100), tôi đưa các chuỗi (dưới dạng con trỏ) vào các "xô" (buckets) tương ứng với độ dài `vector<vector<const string*>> lengthBuckets`.
  * Sau khi chia xô $O(N)$, các chuỗi đã tự động được sắp xếp theo chiều dài. Cuối cùng, chỉ việc gọi Merge Sort (với kỹ thuật dùng con trỏ như trên) cho riêng những xô có nhiều hơn 1 phần tử. Thuật toán này giảm chi phí tổng thể tiệm cận về mốc tuyến tính ở bước phân loại độ dài, đánh bại mọi bẫy về thời gian sinh ra ở phần test case.
