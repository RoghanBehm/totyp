# noweb Typst

A typst backend for literate programming tool **noweb**

## Overview

In typical use of noweb, `noweave` generates documentation by passing the noweb markup stream through the LaTeX backend, producing a `.tex` file which can then be compiled to PDF:
`nw --> markup --> LaTeX --> PDF`


This project replaces the LaTeX step with a Typst emitter:
`nw --> markup --> Typst --> PDF`


## Usage

`build/noweb-typst <markup file name> <code language name>`


> [!NOTE]
> The code language name is passed so that code blocks can be emitted
> with proper syntax highlighting (e.g. ```python).

## Example Output
`latex_out.pdf` is the LaTeX-rendered PDF from compiling the .tex output of `noweave wordcount.nw`.

`typst_out.pdf` is the Typst-rendered PDF from compiling the .typ output (out.typ) of this Typst backend.

Comparison of the two highlights some of the remaining deficiencies in this program. 


### TODO
- Update IR to implement @use
- Add file name and page count to right side of header
- Support @quote and @endquote
- Reconsider @literal implementation