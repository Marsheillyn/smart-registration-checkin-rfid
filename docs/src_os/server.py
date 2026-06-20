import csv
import os
import threading
from datetime import datetime
from flask import Flask, request, jsonify

app = Flask(__name__)

# Mutex Lock untuk sekat Race Condition (Ciri Utama OS - Process Synchronization)
csv_lock = threading.Lock()
CSV_FILE = "runners.csv"

@app.route('/checkin', methods=['POST'])
def checkin():
    data = request.get_json()
    
    # 1. Semak jika data yang dihantar oleh ESP32-S adalah sah
    if not data or 'uid' not in data:
        return jsonify({"status": "Error", "message": "Payload tidak sah!"}), 400
    
    uid = data['uid'].strip().upper()
    updated = False
    runner_name = ""
    current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    
    # 2. Guna Mutex Lock untuk kawal akses fail (Mengelakkan Race Condition)
    with csv_lock:
        all_rows = []
        
        # Baca fail CSV sedia ada jika wujud
        if os.path.exists(CSV_FILE):
            with open(CSV_FILE, mode='r', newline='', encoding='utf-8') as f:
                reader = csv.reader(f)
                for row in reader:
                    all_rows.append(row)
        
        # 3. Cari baris data pelari berdasarkan UID yang di-scan
        for row in all_rows:
            if len(row) > 0 and row[0].strip().upper() == uid:
                runner_name = row[1]
                
                # Jika pelari sudah mendaftar sebelum ini
                if row[2] == "Selesai Check-In":
                    print(f"\n[OS WARNING]: {runner_name} ({uid}) cuba scan kali kedua!")
                    return jsonify({"status": "Warning", "message": f"{runner_name} sudah pun check-in!"}), 200
                
                # Kemas kini Status dan Masa Semasa (OS System Time)
                row[2] = "Selesai Check-In"
                row[3] = current_time
                updated = True
                break
        
        # 4. Tulis semula data yang telah dikemas kini ke dalam fail CSV (Persistent Storage I/O)
        if updated:
            with open(CSV_FILE, mode='w', newline='', encoding='utf-8') as f:
                writer = csv.writer(f)
                writer.writerows(all_rows)
            
            print(f"\n[OS STORAGE] SUCCESS: {runner_name} ({uid}) didaftarkan pada {current_time}!")
            return jsonify({"status": "Success", "message": f"{runner_name} berjaya didaftarkan!"}), 200
        else:
            print(f"\n[OS ERROR] UNKNOWN: Tag UID {uid} tidak wujud dalam fail CSV!")
            return jsonify({"status": "Error", "message": "Kad RFID tidak dikenali dalam fail lokal!"}), 404

if __name__ == '__main__':
    print("\n==================================================================")
    print("[OS SERVER] Mengaktifkan Smart Registration Server (LOKAL EXCEL/CSV)...")
    print(f"[OS INFO] Server berjalan pada IP Laptop kau: http://10.70.27.228:5000")
    print("==================================================================")
    app.run(host='0.0.0.0', port=5000, debug=True)
