# 🛒 ECommerce App

Aplikasi e-commerce desktop berbasis **C++/CLI Windows Forms** dengan database **SQLite**. Mendukung 4 aktor: Admin, Merchant, Customer, dan Courier. Dibuat sebagai proyek akademik untuk mendemonstrasikan konsep pemrograman berorientasi objek, CRUD, dan manajemen database.

---

## ✨ Fitur Utama

### 🔐 Autentikasi
- Login & Registrasi akun
- Role-based access (Admin / Merchant / Customer / Courier)
- Nonaktifkan / aktifkan akun oleh Admin

### 👑 Admin
- **Dashboard** — statistik pengguna, transaksi, dan pendapatan
- **Manajemen User** — tambah, edit, hapus, aktivasi/nonaktivasi user
- **Manajemen Produk** — edit dan hapus produk dari semua merchant
- **Transactions** — lihat semua transaksi, ubah status, hapus transaksi
- **Income** — riwayat pemasukan platform dengan pencarian & filter per tipe (Aplikasi / Merchant / Courier / Withdrawal)

### 🏪 Merchant
- Dashboard pendapatan & statistik penjualan
- CRUD produk (nama, harga, stok, kategori, deskripsi)
- Riwayat penjualan
- Manajemen profil & alamat toko

### 🛍️ Customer
- Browse & beli produk
- Top-up saldo
- Keranjang belanja dengan update kuantitas
- Konfirmasi & batalkan pesanan
- Withdraw saldo
- Riwayat transaksi

### 🚚 Courier
- Dashboard pengiriman harian
- Claim paket yang tersedia (pending deliveries)
- Selesaikan pengiriman aktif
- Riwayat pengiriman & pendapatan

---

## 🗂️ Struktur Proyek

```
ECommerce/
├── mainForm.cpp              # Entry point aplikasi
├── loginForm.h / .cpp        # Form login
├── registrationForm.h / .cpp # Form registrasi
├── adminForm.h / .cpp        # Form admin
├── merchantForm.h / .cpp     # Form merchant
├── customerForm.h / .cpp     # Form customer
├── courierForm.h / .cpp      # Form courier
├── DatabaseManager.h / .cpp  # Semua operasi database (SQLite)
├── sqlite3.h / .c            # SQLite embedded
├── ecommerce.db              # File database SQLite
└── asset/                    # Aset gambar
```

---

## 🏗️ Arsitektur

```
┌─────────────────────────────────────────┐
│             Windows Forms GUI            │
│  Login → [Admin | Merchant | Customer   │
│            | Courier] Form              │
└──────────────────┬──────────────────────┘
                   │
┌──────────────────▼──────────────────────┐
│           DatabaseManager               │
│  (C++/CLI managed wrapper di atas       │
│   native SQLite C API)                  │
└──────────────────┬──────────────────────┘
                   │
┌──────────────────▼──────────────────────┐
│           SQLite Database               │
│  users / products / transactions /      │
│  income tables                          │
└─────────────────────────────────────────┘
```

---

## 🛠️ Teknologi

| Komponen | Detail |
|----------|--------|
| Bahasa | C++/CLI (Managed C++) |
| UI Framework | Windows Forms (WinForms) |
| Database | SQLite (embedded, tanpa server) |
| IDE | Visual Studio 2019 / 2022 |
| Platform | Windows (x64 / x86) |
| Runtime | .NET Framework (CLR) |

---

## 🔄 Alur Sistem

```
Registrasi → Login
               │
       ┌───────┴────────┐
       ▼                ▼
   Customer          Merchant
   Beli Produk       Jual Produk
       │                │
       ▼                ▼
   Transaksi ──→ Courier Klaim
   Dibuat          & Antar
       │
       ▼
   Admin Pantau
   Semua Aktivitas
```

**Alur Keuangan:**
- Customer beli → saldo customer berkurang
- Platform potong fee (income "Aplikasi")
- Merchant terima pembayaran produk (income "Merchant")
- Courier terima ongkir saat antar selesai (income "Courier")

---

## 🚀 Cara Menjalankan

### Prasyarat
- Visual Studio 2019 / 2022 dengan workload **Desktop development with C++** dan **.NET desktop development**
- Windows 10 atau lebih baru

### Langkah
1. Clone repository ini:
   ```bash
   git clone https://github.com/straycut/Project_E-Commerce_App.git
   ```
2. Buka file `ECommerce.vcxproj` di Visual Studio
3. Set konfigurasi ke **Debug** atau **Release** (x64)
4. Tekan **F5** atau klik **Start** untuk build & run

> **Catatan:** Database `ecommerce.db` sudah disertakan. Jika ingin reset data, hapus file tersebut — aplikasi akan membuat database baru secara otomatis saat pertama kali dijalankan.

---

## 🔑 Akun Default

Jika menggunakan database bawaan:

| Username | Password | Role |
|----------|----------|------|
| `admin` | `admin123` | Admin |

Akun Merchant, Customer, dan Courier bisa dibuat melalui halaman Registrasi atau ditambahkan oleh Admin.

---

## 📋 Konsep Pemrograman yang Digunakan

- **OOP** — Class, encapsulation, managed references (`^`)
- **Seleksi** — `if/else`, `switch` untuk routing role
- **Perulangan** — `for each` untuk iterasi DataTable rows
- **Array** — `cli::array<>` untuk statistik dashboard
- **Sorting / Filtering** — Filter DataTable secara manual di memori
- **CRUD** — Create/Read/Update/Delete untuk semua entitas
- **Prepared Statements** — Mencegah SQL Injection via `sqlite3_bind_*`

---

## 📄 Lisensi

Proyek ini dibuat untuk keperluan akademik. Bebas digunakan dan dimodifikasi.
