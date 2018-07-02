IF NOT EXIST opencv\ (
    echo "Cloning OpenCV git repository..."
::    git clone https://github.com/opencv/opencv.git
    mkdir src\opencv2
    xcopy opencv\include\opencv2 src\opencv2 /s
    xcopy opencv\modules src\opencv2 /s
    GOTO installed
) ELSE (
    ECHO "OpenCV already cloned"
)
:installed