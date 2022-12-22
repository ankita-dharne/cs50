from cs50 import get_string

# Get input
text = get_string("Text: ")
len = len(text)
letters = 0
sentences = 0
words = 1
for i in range(0, len):
    # Count letters with the help of ASCII
    if ((text[i] >= 'a' and text[i] <= 'z') or (text[i] >= 'A' and text[i] <= 'Z')):
        letters = letters + 1
    # Count words with every space encountered
    # first word doesn't have space
    if (text[i] == ' '):
        words = words + 1
    # Count sentences with every encountered period, ! & question mark
    if (text[i] == '!' or text[i] == '.' or text[i] == '?'):
        sentences = sentences + 1

# average of letters and sentences per 100 words
L = (100 * (float(letters) / float(words)))
S = (100 * (float(sentences) / float(words)))

# Calculate Coleman-Liau index
index0 = (0.0588 * L) - (0.296 * S) - 15.8
index = (round(index0))

# Result
if (index >= 1 and index < 16):
    print("Grade ", int(index))
elif (index < 1):
    print("Before Grade 1")
else:
    print("Grade 16+")
print("\n")