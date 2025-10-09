# Lamine-yala
# 💻 วิธีคอมไพล์และรันโปรแกรม `final.c`

โปรแกรมนี้เขียนด้วยภาษา **C**  
สามารถคอมไพล์และรันได้ทั้งบน **Windows**, **macOS**, และ **Linux**

---

## 🧩 ขั้นตอนที่ 1: คอมไพล์โปรแกรม

### 🔹 บน **Windows** (ใช้ MinGW หรือ MSYS2)

1. เปิด **Command Prompt** หรือ **PowerShell**  
2. ไปยังโฟลเดอร์ที่มีไฟล์ `final.c`  
3. พิมพ์คำสั่งเพื่อคอมไพล์:

```bash
gcc final.c -o final.exe
เมื่อคอมไพล์เสร็จ จะได้ไฟล์ชื่อ final.exe

🔹 บน macOS / Linux

1. เปิด Terminal
2. ไปยังโฟลเดอร์ที่มีไฟล์ final.c
3. พิมพ์คำสั่งเพื่อคอมไพล์:
gcc final.c -o final
เมื่อคอมไพล์เสร็จ จะได้ไฟล์ชื่อ final

🧩 ขั้นตอนที่ 2: รันโปรแกรม
💠 Windows
.\final.exe
💠 macOS / Linux
./final

⚙️ ขั้นตอนที่ 3: วิธีแก้เมื่อภาษาไทยแสดงไม่ถูกต้อง

หากเมื่อรันโปรแกรมแล้วพบว่า ภาษาไทยแสดงเป็น “????” หรือเป็นตัวอักษรเพี้ยน ให้แก้ไขตามระบบปฏิบัติการดังนี้ 👇

🪟 Windows

เปลี่ยนให้ Command Prompt หรือ PowerShell ใช้รหัส UTF-8:
chcp 65001

🍎 macOS / Linux

ตั้งค่า Locale ให้รองรับ UTF-8:
export LANG=th_TH.UTF-8
export LC_ALL=th_TH.UTF-8
