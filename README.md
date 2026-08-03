# DannyJPark.github.io

Source for my personal academic website.

**Live:** <https://dannyjpark.github.io/>

## About

I'm Hyoungjoon Park (박형준), a Ph.D. student in the Integrated M.S./Ph.D. program in
Computer Science at Yonsei University, advised by Prof. Sanghyun Park. My research is on
AI-driven drug discovery — diffusion models for structure-based drug design (SBDD),
molecular selectivity, and protein–ligand binding affinity prediction.

The site collects my publications, research experience, and projects in one place.

## Structure

```
.
├── index.html                    # the entire site: markup, CSS, and JS in a single file
├── 박형준_사진.jpeg               # profile photo (referenced by <img> and og:image)
├── theselective_overview.png     # Fig. 2 of the PAKDD 2026 paper (1400×630, web-optimized)
├── .gitattributes                # linguist overrides so the repo is classified as HTML
└── README.md
```

There is no build step, no framework, and no dependency to install. Fonts are the only
external resource (Outfit and IBM Plex Mono, loaded from Google Fonts).

Light and dark themes are driven by a `data-theme` attribute on `<html>`. The initial value
is read from `localStorage`, falling back to the operating system's `prefers-color-scheme`.
A small inline script in `<head>` sets it before first paint so the theme never flashes; all
`localStorage` access is wrapped in `try`/`catch`, so the toggle degrades to session-only
rather than throwing where storage is blocked.

## Local preview

```bash
git clone https://github.com/DannyJPark/DannyJPark.github.io.git
cd DannyJPark.github.io
python -m http.server 8000
```

Then open <http://localhost:8000>.

## Editing notes

Everything lives in `index.html`. A few things are coupled and need to be changed together:

| Change | Also update |
|---|---|
| Profile photo | `<img>` in the sidebar **and** `og:image` in `<head>` |
| Adding a section | The `<div class="section" id="…">` **and** the matching `<a href="#…">` in `<nav class="sidebar-nav">` |
| Name, links, affiliation | The visible markup **and** the `application/ld+json` block in `<head>` |
| Theme colors | Both `:root` **and** `:root[data-theme="dark"]`, plus the dark-override block at the end of the stylesheet |

The publication results table is transcribed from the published paper; if a number changes
there, change it here too.

`theselective_overview.png` is Figure 2 of the PAKDD 2026 paper, downscaled to 1400 px wide
and colour-quantized for the web. Regenerate it from the original figure rather than
upscaling this copy.

## Deployment

GitHub Pages serves the `main` branch from the repository root. Pushing to `main` deploys.

## Contact

- Email: <ktori1361@yonsei.ac.kr>
- ORCID: <https://orcid.org/0009-0003-0721-1716>
- Google Scholar: <https://scholar.google.com/citations?user=TJPGDTUAAAAJ>
- LinkedIn: <https://www.linkedin.com/in/ktori1361/>

## License

The site's code (HTML, CSS, JavaScript) is released under the [MIT License](LICENSE).

Personal content — the profile photo, biography, publication list, and CV material — is
**not** covered by that license and remains © 2026 Hyoungjoon Park, all rights reserved.
