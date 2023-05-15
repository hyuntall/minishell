# MiniShell

MiniShell은 순수 C 언어를 사용하여 개발된 축소판 bash shell입니다. 이 프로젝트는 기본적인 명령어와 몇 가지 추가 기능을 구현하여 사용자가 프로그램을 실행하고 관리할 수 있도록 합니다. MiniShell은 make 명령어와 makefile을 사용하여 컴파일할 수 있으며, "./minishell"을 입력하여 프로그램을 실행할 수 있습니다.

## 기능

- 기본 명령어 구현: MiniShell은 echo, cat 등과 같은 일반적인 명령어들을 구현하여 사용자가 파일을 읽거나 출력할 수 있도록 합니다.
- 파이프라인: MiniShell은 파이프라인 기능을 지원하여 두 개 이상의 명령어를 연결하고 출력을 전달할 수 있도록 합니다.
- &&와 || 연산자: MiniShell은 명령어를 실행하고 성공 또는 실패에 따라 다음 명령어를 실행할지 결정할 수 있는 &&와 || 연산자를 구현하여 사용자에게 유연성을 제공합니다.

## 사용 방법

1. 프로젝트를 클론합니다:

```shell
git clone https://github.com/hyuntall/minishell.git
```

2. 프로젝트 폴더로 이동합니다:

```shell
cd minishell
```

3. make 명령어를 사용하여 프로젝트를 컴파일합니다:

```shell
make
```

4. 컴파일된 MiniShell을 실행합니다:

```shell
./minishell
```

5. MiniShell에서 지원하는 명령어를 입력하여 프로그램을 사용합니다.

## 참고 사항

- MiniShell은 bash shell의 축소판으로, 일부 기능이나 명령어는 지원하지 않을 수 있습니다.
- MiniShell은 실제 사용을 목적으로 하는 완전한 shell이 아니며, 학습 및 개인적인 목적으로 사용될 것을 권장합니다.

