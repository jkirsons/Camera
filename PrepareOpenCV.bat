IF EXIST opencv\ (
    echo "Cloning OpenCV git repository..."
::    git clone https://github.com/opencv/opencv.git
    mkdir lib\opencv2
    xcopy opencv\include\opencv2 lib\opencv2 /s
    xcopy opencv\modules lib\opencv2 /s
    GOTO installed
) ELSE (
    ECHO "OpenCV already cloned"
)
:installed