@rem Author:Õı‚Ÿ date:2014-11-16 TODO:custom out put dir, if not,use default  
@echo off  
echo ***************create new project*****************
echo ****************AuthorÕı‚Ÿ********************
echo ****************Coding, Playing******************

set /p name=please enter project_name:
echo project_name is:%name%
set pn=com.pku.game.android.newstart
set /p pn=please enter package_name:
echo package_name is:%pn% 
set path=%~dp0\projects\
set /p path=please enter project directory:
echo project directory is:%path%
echo processing creation task...  

%~dp0\tools\cocos2d-console\bin\cocos.py new %name% -p %name% -l cpp -d %path%
  
echo enter directory....  
  
cd %path%\%name%  
  
pause 