<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<div align="center">
<!--
  <a href="https://github.com/Madahin/BobTheChessEngine">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>
-->
<h3 align="center">Bob the Chess Engine</h3>

  <p align="center">
    An UCI compatible chess engine for fun
    <br />
    <a href="https://github.com/Madahin/BobTheChessEngine/issues">Report Bug</a>
    ·
    <a href="https://github.com/Madahin/BobTheChessEngine/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#compilation">Compilation</a></li>
      </ul>
    </li>
    <li>
      <a href="#usage">Usage</a></li>
      <ul>
        <li><a href="#chess-frontend">Chess frontend</a></li>
        <li><a href="#testing">Testing</a></li>
      </ul>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li>
      <a href="#acknowledgments">Acknowledgments</a>
      <ul>
        <li><a href="#people">People</a></li>
        <li><a href="#documentation">Documentation</a></li>
        <li><a href="#technologies-used">Technologies used</a></li>
      </ul>
    </li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

<!--[![Product Name Screen Shot][product-screenshot]](https://example.com)-->

Bob is just a simple chess engine with no pretention.

I love chess, but i'm really bad at it, so I tough I could make an engine that would be
as good as I'm meant to be.


Bob is meant to be compatible with UCI, so any chess frontend compatible with the protocl should
be able to use him. I personaly use [KNights](https://apps.kde.org/knights/) to develop him.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started
The project is being developped on linux. As such, I have no idea if it can be built on Windows or macOS.

That said, a cmake toolchain is provided for Windows cross-compilation.

### Prerequisites

All dependencies are taken care of in cmake, so you just need compiler compatible with C++17 and cmake.

On archlinux, this should suffice :
  ```sh
  pacman -S base-devel cmake
  ```

If you want to cross-compile for Windows, you will also need mingw64

On archlinux, the package is mingw-w64 :
  ```sh
  pacman -S mingw-w64
  ```

### Compilation

1. Clone the repo
   ```sh
   git clone https://github.com/Madahin/BobTheChessEngine
   ```
2. Make a build directory and `cd` into it
   ```sh
   mkdir BobTheChessEngine/build && cd BobTheChessEngine/build
   ```
3. Build the project
   ```sh
   cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/Toolchain-gcc-m64.cmake
   make
   ```
   
You can choose different toolchains depending on your needs :
* Linux x86 : Toolchain-gcc-m32.cmake
* Linux x64 : Toolchain-gcc-m64.cmake
* Windows x86 : Toolchain-mingw64-m64.cmake
* Windows x64 : Toolchain-mingw64-m64.cmake

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

### Chess frontend
TODO: explain how to use KNight

### Testing
You can launch the unit tests with 
``` sh
./build/test/BobTheChessEngine_test
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ROADMAP -->
## Roadmap

- [ ] Finishing the readme
    - [ ] Writing the USAGE section
    - [x] Finishing the roadmap
- [ ] UCI Interface
    - [ ] Gui -> Engine
        - [x] ucinewgame
        - [x] uci
        - [x] quit
        - [x] debug
        - [x] option
        - [x] isready
        - [ ] setoption name <id> [value <x>]
        - [ ] position [fen <fenstring> | startpos ] moves <move1> .... <movei>
        - [ ] go
        - [ ] stop
        - [ ] ponderhit
    - [ ] Engine -> GUI
        - [x] id
        - [x] uciok
        - [x] readyok
        - [ ] bestmove <move1> [ ponder <move2> ]
        - [ ] info
        - [ ] option
- [ ] Passing the generation move test suite
- [ ] Playing random legal move
- [ ] Improving AI

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing


Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Madahin - [@madahin](https://twitter.com/madahin) - [@Madahin@qoto.org](https://qoto.org/@Madahin)

Project Link: [https://github.com/Madahin/BobTheChessEngine](https://github.com/Madahin/BobTheChessEngine)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

### People
* [Sebastian Lague](https://github.com/SebLague) for his incredible [coding adventure video](https://www.youtube.com/watch?v=U4ogK0MIzqk)

### Documentation
* [Chess Programming Wiki](https://www.chessprogramming.org)
* [shredderchess.com](https://www.shredderchess.com/) for the UCI specification

### Technologies used
* [cmake](https://cmake.org/)
* [google test](https://github.com/google/googletest)
* [spdlog](https://github.com/gabime/spdlog)
* [Best-README-Template](https://github.com/othneildrew/Best-README-Template)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/Madahin/BobTheChessEngine.svg?style=for-the-badge
[contributors-url]: https://github.com/Madahin/BobTheChessEngine/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/Madahin/BobTheChessEngine.svg?style=for-the-badge
[forks-url]: https://github.com/Madahin/BobTheChessEngine/network/members
[stars-shield]: https://img.shields.io/github/stars/Madahin/BobTheChessEngine.svg?style=for-the-badge
[stars-url]: https://github.com/Madahin/BobTheChessEngine/stargazers
[issues-shield]: https://img.shields.io/github/issues/Madahin/BobTheChessEngine.svg?style=for-the-badge
[issues-url]: https://github.com/Madahin/BobTheChessEngine/issues
[license-shield]: https://img.shields.io/github/license/Madahin/BobTheChessEngine.svg?style=for-the-badge
[license-url]: https://github.com/Madahin/BobTheChessEngine/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/nicolas-fleurot/
[product-screenshot]: images/screenshot.png
