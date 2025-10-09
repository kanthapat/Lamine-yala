# Lamine-yala
# 💻 วิธีคอมไพล์และรันโปรแกรม `final.c`

โปรแกรมนี้เขียนด้วยภาษา **C**  
สามารถคอมไพล์และรันได้ทั้งบน **Windows**, **macOS**, และ **Linux**

---

## 🧩 1. คอมไพล์โปรแกรม

### 🔹 บน Windows (ใช้ MinGW หรือ MSYS2)

1. เปิด **Command Prompt** หรือ **PowerShell**
2. ไปยังโฟลเดอร์ที่มีไฟล์ `final.c`
3. ใช้คำสั่ง:
   ```bash
   gcc -o final.exe final.c
เมื่อคอมไพล์เสร็จ จะได้ไฟล์ final.exe

🔹 บน macOS / Linux
เปิด Terminal

ไปยังโฟลเดอร์ที่มีไฟล์ final.c

ใช้คำสั่ง:

bash
คัดลอกโค้ด
gcc -o final final.c
เมื่อคอมไพล์เสร็จ จะได้ไฟล์ชื่อ final

▶️ 2. รันโปรแกรม
🔸 Windows
bash
คัดลอกโค้ด
.\final.exe
🔸 macOS / Linux
bash
คัดลอกโค้ด
./final
⚙️ 3. วิธีแก้เมื่อภาษาไทยแสดงไม่ถูกต้อง
ถ้าเมื่อรันโปรแกรมแล้วพบว่า ภาษาไทยแสดงเป็น “????” หรือเป็นตัวอักษรเพี้ยน,
ให้แก้ไขตามระบบปฏิบัติการดังนี้ 👇

🪟 Windows
เปลี่ยนให้ Command Prompt หรือ PowerShell ใช้รหัส UTF-8
พิมพ์คำสั่ง:

bat
คัดลอกโค้ด
chcp 65001