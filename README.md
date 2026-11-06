# Inverted Search – VS Code C Project

This project implements the method in the supplied **InvertedSearch** specification:
- Read filenames from `data/filelist.txt`.
- Parse each text file into alphabetic words.
- Store unique words in an alphabetically sorted **singly linked list**.
- For each word, maintain a linked list of filenames and occurrence counts.
- Search the in-memory index and report the files and counts.
- Save a readable database backup to `output/database.txt`.

The menu follows the sample: Create, Display, Update, Search, Save. `0. Exit` is included as a convenience.

## 1. Folder structure

```text
InvertedSearch_VSCode/
├── main.c
├── inverted_search.h
├── indexing.c
├── database.c
├── search.c
├── data/
│   ├── filelist.txt
│   ├── file1.txt
│   └── file2.txt
├── output/
│   └── database.txt       (created when you choose Save)
├── .vscode/
│   ├── tasks.json
│   └── launch.json
└── README.md
```

## 2. Install compiler

Install **MinGW-w64 GCC** and make sure `gcc` is available in the VS Code terminal.

Check:

```bash
gcc --version
```

If the command is not recognized, add the MinGW `bin` folder to Windows PATH, restart VS Code, and try again.

## 3. Build

Open this folder in VS Code. Open **Terminal → New Terminal** and run:

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c indexing.c database.c search.c -o inverted_search.exe
```

## 4. Run

In the VS Code terminal:

```powershell
.\inverted_search.exe
```

On Linux/macOS:

```bash
./inverted_search
```

Run the program from the project root folder so the relative paths under `data/` and `output/` work.

## 5. How to use the menu

1. **Create DATABASE** – reads every filename listed in `data/filelist.txt` and builds the index.
2. **Display Database** – prints the sorted word list, number of files containing each word, and each file's occurrence count.
3. **Update DATABASE** – enter a path such as `data/file2.txt`. The file is indexed and appended to `data/filelist.txt`.
4. **Search** – enter one or more words. Each word is searched and matching filenames/counts are printed.
5. **Save Database** – writes a backup to `output/database.txt`.
0. **Exit** – releases allocated linked-list memory and exits.

## 6. Add your own text files

1. Copy your `.txt` files into the `data` folder.
2. Open `data/filelist.txt`.
3. Add one relative path per line, for example:

```text
data/file1.txt
data/file2.txt
data/my_notes.txt
```

4. Run the program and choose `1`.

Do not put blank lines or folder headings in the file list. Lines beginning with `#` are ignored.

## 7. Example test

The included `file1.txt` and `file2.txt` are small demonstration inputs. To reproduce the sample's create-then-update flow:

1. Choose `1` to create the initial database from `filelist.txt` (which initially contains only `data/file1.txt`).
2. Choose `3` and enter `data/file2.txt` to add the second file.
3. Choose `4` and search for `Hi`.

The search output should report:
- `data/file1.txt` – 6 occurrences
- `data/file2.txt` – 1 occurrence

The exact display order is based on the filenames in `filelist.txt`.

## 8. Notes about the implementation

- Words are **case-sensitive**, matching the capitalization shown in the supplied sample. `Hi`, `hi`, and `HI` are treated as different words.
- A word consists of alphabetic characters. Spaces, punctuation, digits, and line breaks delimit words. Therefore punctuation such as `?` is not indexed as a word.
- All words are indexed; stop-word removal is not enabled because the supplied sample database displays common words such as `are` and `you`.
- The database is held in memory while the program runs. Choose **Save Database** to write the backup. The current program rebuilds the index from `filelist.txt` when option 1 is selected; it does not load a previously saved backup automatically.
- The linked list is kept sorted, so search can stop early when the current indexed word is alphabetically greater than the search word.

## 9. Troubleshooting

**`cannot open input file`**: Check the spelling and relative path in `data/filelist.txt`.

**`gcc is not recognized`**: Install MinGW-w64 GCC, add its `bin` directory to PATH, then restart VS Code.

**Program says database is empty**: Choose option `1` before Display or Search.

**File appears twice in filelist**: Remove duplicate lines from `data/filelist.txt` before rebuilding.
