@file wordcount.nw
@begin docs 0
@text \section{A tiny word counter}
@nl
@text 
@nl
@text We will build a minimal word counter and explain its parts.
@nl
@text The program runs in $O(n)$ over the bytes of the input.
@nl
@text We assemble the final script in the chunk \verb|<<wc.py>>=| by
@nl
@text referring to named subchunks that we define later.
@nl
@text 
@nl
@end docs 0
@begin code 1
@defn wc.py
@nl
@use imports
@text 
@nl
@use parse-args
@text 
@nl
@use count-words
@text 
@nl
@use main-guard
@text 
@nl
@end code 1
@begin docs 2
@text 
@nl
@text 
@nl
@text \subsection{Imports}
@nl
@text 
@nl
@end docs 2
@begin code 3
@defn imports
@nl
@text import sys
@nl
@text from collections import Counter
@nl
@text from pathlib import Path
@nl
@text import argparse
@nl
@end code 3
@begin docs 4
@text 
@nl
@text 
@nl
@text \subsection{Argument parsing}
@nl
@text 
@nl
@end docs 4
@begin code 5
@defn parse-args
@nl
@text def parse_args(argv=None):
@nl
@text     p = argparse.ArgumentParser(
@nl
@text         description="Count words in a file or stdin."
@nl
@text     )
@nl
@text     p.add_argument("file", nargs="?", help="Path to text file; default: stdin")
@nl
@text     p.add_argument("-n", "--top", type=int, default=10,
@nl
@text                    help="Show top-N words (default: 10)")
@nl
@text     return p.parse_args(argv)
@nl
@end code 5
@begin docs 6
@text 
@nl
@text 
@nl
@text \subsection{Counting logic}
@nl
@text 
@nl
@end docs 6
@begin code 7
@defn count-words
@nl
@text def words_from_text(text: str):
@nl
@text     # Very naive tokenization: split on whitespace and punctuation
@nl
@text     # Lowercasing makes counts case-insensitive.
@nl
@text     import re
@nl
@text     for w in re.findall(r"[A-Za-z0-9']+", text.lower()):
@nl
@text         yield w
@nl
@text 
@nl
@text def count_words(stream) -> Counter:
@nl
@text     c = Counter()
@nl
@text     for line in stream:
@nl
@text         c.update(words_from_text(line))
@nl
@text     return c
@nl
@end code 7
@begin docs 8
@text 
@nl
@text 
@nl
@text \subsection{Program entry point}
@nl
@text 
@nl
@end docs 8
@begin code 9
@defn main-guard
@nl
@text def main(argv=None):
@nl
@text     args = parse_args(argv)
@nl
@text     if args.file:
@nl
@text         data = Path(args.file).read_text(encoding="utf-8", errors="ignore")
@nl
@text         stream = data.splitlines(keepends=True)
@nl
@text     else:
@nl
@text         stream = sys.stdin
@nl
@text 
@nl
@text     counts = count_words(stream)
@nl
@text     for word, n in counts.most_common(args.top):
@nl
@text         print(f"{n:7d}  {word}")
@nl
@text 
@nl
@text if __name__ == "__main__":
@nl
@text     main()
@nl
@end code 9
@begin docs 10
@text 
@nl
@end docs 10
