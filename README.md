# Library Management System

> C++17 · OOP · Excel (xlnt) · Pretty tables (tabulate)

---

## Project Structure

```
LibrarySystem/
├── CMakeLists.txt
├── main.cpp                        ← entry point
│
├── include/                        ← all header files (.hpp)
│   ├── book/
│   │   └── Book.hpp
│   ├── core/
│   │   ├── Admin.hpp
│   │   ├── BorrowRecord.hpp
│   │   ├── ExcelUtils.hpp
│   │   ├── History.hpp
│   │   ├── Librarian.hpp
│   │   ├── LogIn.hpp
│   │   ├── SignUp.hpp
│   │   └── User.hpp
│   ├── security/
│   │   ├── HidePwd.hpp
│   │   └── Password.hpp
│   ├── ui/
│   │   ├── Animation.hpp
│   │   └── LabelMenu.hpp
│   ├── utils/
│   │   ├── Logger.hpp
│   │   └── Utils.hpp
│   └── validation/
│       └── Validation.hpp
│
├── src/                            ← implementation files (.cpp)
│   ├── core/
│   │   ├── admin.cpp
│   │   ├── excelUtils.cpp
│   │   ├── librarian.cpp
│   │   ├── logIn.cpp
│   │   └── signUp.cpp
│   ├── ui/
│   │   ├── animation.cpp
│   │   └── labelMenu.cpp
│   ├── utils/
│   │   ├── logger.cpp
│   │   └── utils.cpp
│   └── validation/
│       └── validation.cpp
│
└── data/                           ← data-layer files + Excel files
    ├── book/
    │   └── book.cpp
    └── security/
        ├── hidePwd.cpp
        ├── password.cpp
        └── accounts.xlsx           ← generated on first run
```

---

## Dependencies

| Library   | Purpose             | Install                            |
|-----------|---------------------|------------------------------------|
| `xlnt`    | Excel read / write  | `sudo apt install libxlnt-dev`     |
| `tabulate`| Pretty console tables | Clone + copy headers to `include/`|

```bash
# tabulate (header-only)
git clone https://github.com/p-ranav/tabulate
cp -r tabulate/include/tabulate include/
```

---

## Build

```bash
cmake -B build
cmake --build build
./build/library          # Linux / macOS
build\library.exe        # Windows
```

Or compile directly:

```bash
g++ -std=c++17 \
    main.cpp data/book/book.cpp data/security/*.cpp \
    src/core/*.cpp src/ui/*.cpp src/utils/*.cpp src/validation/*.cpp \
    -I include -o library -lxlnt
```

---

## Default Accounts (created on first run)

| Username | Password | Role       |
|----------|----------|------------|
| Lyheng   | 070308   | admin      |
| Phykay   | 150207   | librarian  |
| Nary     | 168168   | user       |

---

## Role Permissions

| Feature          | Admin | Librarian | User |
|------------------|:-----:|:---------:|:----:|
| Add Book         | ✅    | ❌        | ❌   |
| Edit Book        | ✅    | ❌        | ❌   |
| Delete Book      | ✅    | ❌        | ❌   |
| Show All Books   | ✅    | ✅        | ✅   |
| Search Book      | ✅    | ✅        | ✅   |
| Borrow Book      | ✅    | ✅        | ✅ (max 3) |
| Return Book      | ✅    | ✅ (all)  | ✅ (own) |
