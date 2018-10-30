#include "dxgraphics.h"

LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev = NULL;
LPDIRECT3DSURFACE9 backbuffer = NULL;

int Init_Direct3D(HWND hWnd, int width, int height) {
	//Init Direct3D
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == NULL) {
		MessageBox(hWnd, "Error initializing Direct3D", "Error", MB_OK);
		return 0;
	}
	//set Direct3D presentation parameters
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = true; // Window ở dạng cửa sổ, không phải full màn hình
	d3dpp.BackBufferCount = 1; // Số lượng Back buffer
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Chọn UNKNOW, DirectX sẽ tự chọn 1 định dạng phù hợp cho Device
	d3dpp.BackBufferHeight = height; // chiều cao cảu BackBuffer
	d3dpp.BackBufferWidth = width; // Chiều dài của BackBuffer
	d3dpp.hDeviceWindow = hWnd; // Gán HandleWindow cho Device
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // Phương thức swap của Buffer

	//create Direct3D device
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev
	);

	if (d3ddev == NULL) {
		MessageBox(hWnd, "Error creating Direct3D device", "Error", MB_OK);
		return 0;
	}

	//clear the backbuffer to black
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//create pointer to the back buffer
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

	return 1;
}

LPDIRECT3DSURFACE9 LoadSurface(char *filename, D3DCOLOR transcolor) {
	LPDIRECT3DSURFACE9 image = NULL;
	D3DXIMAGE_INFO info;
	HRESULT result;

	//get width and height from bitmap file
	result = D3DXGetImageInfoFromFile(filename, &info);
	if (result != D3D_OK) {
		return NULL;
	}
	//create surface
	result = d3ddev->CreateOffscreenPlainSurface(
		info.Width, //width of the surface
		info.Height,
		D3DFMT_X8R8G8B8, //surface format
		D3DPOOL_DEFAULT, //memory pool to use
		&image, //pointer to the surface
		NULL //reserved (always NULL)
	);

	if (result != D3D_OK) {
		return NULL;
	}

	//load surface from file into newly created surface
	result = D3DXLoadSurfaceFromFile(
		image, //destination surface
		NULL, //destination palette
		NULL, //destination rectangle
		filename, //source filename
		NULL, //source rectangle
		D3DX_DEFAULT, //controls how image is filtered
		transcolor, //for transparency (0 for none)
		NULL //source image info (usually NULL)
	);

	//make sure file was loaded okay
	if (result != D3D_OK) {
		return NULL;
	}
	return image;
}