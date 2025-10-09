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

ใช้คำสั่ง: gcc -o final final.c

เมื่อคอมไพล์เสร็จ จะได้ไฟล์ชื่อ final

▶️ 2. รันโปรแกรม
🔸 Windows
.\final.exe
🔸 macOS / Linux
./final

⚙️ 3. วิธีแก้เมื่อภาษาไทยแสดงไม่ถูกต้อง
ถ้าเมื่อรันโปรแกรมแล้วพบว่า ภาษาไทยแสดงเป็น “????” หรือเป็นตัวอักษรเพี้ยน,
ให้แก้ไขตามระบบปฏิบัติการดังนี้ 👇

🪟 Windows
เปลี่ยนให้ Command Prompt หรือ PowerShell ใช้รหัส UTF-8
พิมพ์คำสั่ง: chcp 65001

🍎 macOS / 🐧 Linux

ตรวจสอบว่า Terminal ใช้ UTF-8 ด้วยคำสั่ง:

echo $LANG

ค่าที่ถูกต้องควรเป็น th_TH.UTF-8 หรือ en_US.UTF-8

ถ้าไม่ใช่ ให้ตั้งค่าชั่วคราวใน Terminal ด้วย:

export LANG=th_TH.UTF-8
export LC_ALL=th_TH.UTF-8

จากนั้นลองรันโปรแกรมอีกครั้ง:

./final
