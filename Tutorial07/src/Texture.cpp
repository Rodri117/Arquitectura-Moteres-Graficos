#include "Texture.h"
#include "Device.h"
#include "DeviceContext.h"

void
Texture::destroy() {
	if (m_texture != nullptr) {
		SAFE_RELEASE(m_textureFromImg);
	}
}

void
Texture::init(Device device, std::string TextureName) {
	if (device.m_device == nullptr) {
		WARNING("ERROR: Texture::init : [CREATION OF RESOURCE : FALSE] [CHACK FOR Device device] \n");
		exit(1);
	}
	HRESULT hr = S_OK;
	hr = D3DX11CreateShaderResourceViewFromFile(device.m_device,
		TextureName.c_str(),
		nullptr,
		nullptr,
		&m_textureFromImg,
		nullptr);

	if (FAILED(hr)) {
		WARNING("ERROR: Texture::init : [CREATION OF RESOURCE : FLASE] [CHECK FOR correct texture name in Filepath] \n");
		exit(1);
	}
}

void Texture::init(Device device,
	unsigned int width,
	unsigned int height,
	DXGI_FORMAT format,
	unsigned int BindFlags) {
	
	if (device.m_device == nullptr) {
		WARNING("ERROR: Texture::init : [CREATION OF RESORCE : FALSE] [CHECK FOR Device device] \n");
		exit(1);
	}

	if (width <= 0 || height <= 0) {
		WARNING("ERROR: Texture::init : [CREATION OF RESORCE : FALSE] [CHECK FOR Width or heigth] \n");
		exit(1);
	}

	HRESULT hr = S_OK;

	D3D11_TEXTURE2D_DESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = format;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = BindFlags;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	if (BindFlags == D3D11_BIND_DEPTH_STENCIL) {
		hr = device.CreateTexture2D(&desc, nullptr, &m_texture);
	}

	if (m_texture == nullptr) {
		WARNING("ERROR: Texture::init : [CREATION OF RESORCE : FALSE] [CHECK FOR m_texture] \n");
		exit(1);
	}
	else if (FAILED(hr)) {
		WARNING("ERROR: Texture::init : [CREATION OF RESORCE : FALSE] [CHECK FOR CreateTexture2D] \n");
		exit(1);
	}
}

void
Texture::update() {

}

void
Texture::render(DeviceContext& deviceContext) {
	deviceContext.PSSetShaderResources(0, 1, &m_textureFromImg);
}
