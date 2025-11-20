#include <bits/stdc++.h>
using namespace std;

bool isKeyValid(string &key)
{
  int n = key.length();
  if (n == 0 || n > 9)
  {
    cout << "Error: Key length must be between 1 and 9.\n";
    return false;
  }

  vector<bool> seen(n + 1, false);
  for (char ch : key)
  {
    if (!isdigit(ch))
    {
      cout << "Error: Key must contain only digits.\n";
      return false;
    }
    int digit = ch - '0';
    if (digit == 0 || digit > n)
    {
      cout << "Error: Key digits must be in the range [1, " << n << "].\n";
      return false;
    }
    if (seen[digit])
    {
      cout << "Error: Key contains duplicate digits.\n";
      return false;
    }
    seen[digit] = true;
  }
  return true;
}

string columnarEncrypt(string &text, string &key)
{
  int cols = key.size();
  int rows = ceil((double)text.size() / cols);
  vector<vector<char>> matrix(rows, vector<char>(cols, '_'));

  int idx = 0;
  for (int r = 0; r < rows; r++)
    for (int c = 0; c < cols; c++)
      if (idx < text.size())
        matrix[r][c] = text[idx++];

  cout << "\n[Columnar Matrix for Encryption]\n";
  for (const auto &row : matrix)
  {
    for (char ch : row)
      cout << ch << " ";
    cout << "\n";
  }

  //  <dig, oci>.
  vector<pair<int, int>> keyOrder;
  for (int i = 0; i < cols; i++)
  {
    keyOrder.push_back({key[i] - '0', i});
  }

  sort(keyOrder.begin(), keyOrder.end());

  cout << "[Key Sorting Order (Digit, Original Column Index)]:\n";
  for (const auto &p : keyOrder)
    cout << p.first << "(" << p.second << ") ";
  cout << "\n";

  string cipher;
  for (const auto &p : keyOrder)
  {
    int col = p.second; // org col ind
    for (int r = 0; r < rows; r++)
    {
      if (matrix[r][col] != '_')
      {
        cipher.push_back(matrix[r][col]);
      }
    }
  }
  return cipher;
}

string columnarDecrypt(const string &cipher, const string &key)
{
  int cols = key.size();
  int rows = ceil((double)cipher.size() / cols);

  int num_full_cols = cipher.size() % cols;
  if (num_full_cols == 0 && !cipher.empty())
  {
    num_full_cols = cols;
  }

  // Recreate the same key order as in encryption
  vector<pair<int, int>> keyOrder;
  for (int i = 0; i < cols; i++)
    keyOrder.push_back({key[i] - '0', i});
  sort(keyOrder.begin(), keyOrder.end());

  vector<vector<char>> matrix(rows, vector<char>(cols, '_'));
  int cipher_idx = 0;

  for (int k = 0; k < cols; k++)
  {
    int original_col_idx = keyOrder[k].second;

    int len_of_this_col = (original_col_idx < num_full_cols) ? rows : rows - 1;

    for (int r = 0; r < len_of_this_col; r++)
    {
      if (cipher_idx < cipher.size())
      {
        matrix[r][original_col_idx] = cipher[cipher_idx++];
      }
    }
  }

  cout << "\n[Columnar Decryption Matrix]\n";
  for (const auto &row : matrix)
  {
    for (char ch : row)
      cout << ch << " ";
    cout << "\n";
  }

  string plain;
  for (int r = 0; r < rows; r++)
    for (int c = 0; c < cols; c++)
      if (matrix[r][c] != '_')
        plain.push_back(matrix[r][c]);

  return plain;
}

int main()
{
  while (true)
  {
    cout << "\n COLUMNAR TRANSPOSITION CIPHER \n";
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    cout << "3. Quit\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;

    if (cin.fail())
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input. Please enter a number.\n";
      continue;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 3)
      break;

    string text, key;

    if (choice == 1)
    {
      cout << "Enter plaintext: ";
      getline(cin, text);
      cout << "Enter key (numbers): ";
      getline(cin, key);

      if (!isKeyValid(key))
      {
        continue;
      }

      string cipher = columnarEncrypt(text, key);
      cout << "Ciphertext: " << cipher << "\n";
    }
    else if (choice == 2)
    {
      cout << "Enter ciphertext: ";
      getline(cin, text);
      cout << "Enter key (): ";
      getline(cin, key);

      if (!isKeyValid(key))
      {
        continue;
      }

      string plain = columnarDecrypt(text, key);
      cout << "Decrypted text: " << plain << "\n";
    }
    else
    {
      cout << "Invalid choice!\n";
    }
  }

  cout << "Exiting program.\n"; // 4312567
  return 0;
}
