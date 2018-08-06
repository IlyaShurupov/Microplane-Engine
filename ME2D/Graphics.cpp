//============================================================================
// Microplane Engine - ME2D
//----------------------------------------------------------------------------
// Copyright (c) 2018 Ivan Kmeťo
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//	  claim that you wrote the original software. If you use this software
//	  in a product, an acknowledgment in the product documentation would be
//	  appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//	  misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//
//============================================================================

#include "stdafx.h"
#include "Graphics.h"
#include "Logger.h"


void ASSERT_D3D(HRESULT value, std::string description, std::string msgboxTitle) {
	MessageBox(nullptr, description.c_str(), msgboxTitle.c_str(), MB_OK | MB_ICONERROR);
	Log_Open("debug.log");
	Error(value);
	Log_Write(description);
	Log_Close();
}

Graphics::Graphics()
{
	m_pFactory = NULL;
	m_pRenderTarget = NULL;
	m_pMainBrush = NULL;
	m_pFillBrush = NULL;
}

Graphics::~Graphics()
{
	if (m_pFillBrush) m_pFillBrush->Release();
	if (m_pMainBrush) m_pMainBrush->Release();
	if (m_pRenderTarget) m_pRenderTarget->Release();
	if (m_pFactory) m_pFactory->Release();
}

bool Graphics::Init(HWND windowHandle)
{
	HRESULT errchck001 = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);
	if (errchck001 != S_OK) {
		ASSERT_D3D(errchck001, "[ERRD2D1001] D2D1 Factory failed to initialize!", "Error");
		return false;
	}

	RECT rect;
	GetClientRect(windowHandle, &rect);

	HRESULT errchck002 = m_pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)), &m_pRenderTarget);
	if (errchck002 != S_OK) {
		ASSERT_D3D(errchck002, "[ERRD2D1002] D2D1 Factory failed to create ID2D1HwndRenderTarget!", "Error");
		return false;
	}

	HRESULT errchck003 = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &m_pMainBrush);
	if (errchck003 != S_OK) {
		ASSERT_D3D(errchck003, "[ERRD2D1003] Failed to create Solid Color Brush!", "Error");
		return false;
	}

	HRESULT errchck004 = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &m_pFillBrush);
	if (errchck004 != S_OK) {
		ASSERT_D3D(errchck004, "[ERRD2D1004] Failed to create Solid Color Brush!", "Error");
		return false;
	}

	return true;
}


void Graphics::ClearScreen(float r, float g, float b)
{
	m_pRenderTarget->Clear(D2D1::ColorF(r, g, b));
}


//-----------------------------------------------[OBJECTS: 2D GEOMETRY]-----------------------------------------------

void Graphics::RenderCircleRGBA(float x, float y, float radius, float r, float g, float b, float a, float strokesize) {
	m_pMainBrush->SetColor(D2D1::ColorF(r, g, b, a));

	D2D1_ELLIPSE circle = D2D1::Ellipse(
		D2D1::Point2F(x, y),
		radius,
		radius
	);
	m_pRenderTarget->DrawEllipse(circle, m_pMainBrush, strokesize);
}

void Graphics::RenderCircleRGBAF(float x, float y, float radius, float r, float g, float b, float a, float strokesize) {
	m_pMainBrush->SetColor(D2D1::ColorF(r, g, b, a));
	m_pFillBrush->SetColor(D2D1::ColorF(r, g, b, a));

	D2D1_ELLIPSE circle = D2D1::Ellipse(
		D2D1::Point2F(x, y),
		radius,
		radius
	);
	m_pRenderTarget->DrawEllipse(circle, m_pMainBrush, strokesize);
	m_pRenderTarget->FillEllipse(circle, m_pFillBrush);
}

void Graphics::RenderCircleRGBASF(float x, float y, float radius, float r, float g, float b, float a, float strokesize, float fill_r, float fill_g, float fill_b, float fill_a) {
	m_pMainBrush->SetColor(D2D1::ColorF(r, g, b, a));
	m_pFillBrush->SetColor(D2D1::ColorF(fill_r, fill_g, fill_b, fill_a));

	D2D1_ELLIPSE circle = D2D1::Ellipse(
		D2D1::Point2F(x, y),
		radius,
		radius
	);
	m_pRenderTarget->DrawEllipse(circle, m_pMainBrush, strokesize);
	m_pRenderTarget->FillEllipse(circle, m_pFillBrush);
}


void Graphics::RenderEllipseRGBA(float x, float y, float xRadius, float yRadius, float r, float g, float b, float a, float strokesize) {
	m_pMainBrush->SetColor(D2D1::ColorF(r, g, b, a));

	D2D1_ELLIPSE ellipse = D2D1::Ellipse(
		D2D1::Point2F(x, y),
		xRadius,
		yRadius
	);
	m_pRenderTarget->DrawEllipse(ellipse, m_pMainBrush, strokesize);
}

void Graphics::RenderEllipseRGBAF(float x, float y, float xRadius, float yRadius, float r, float g, float b, float a, float strokesize) {
	m_pMainBrush->SetColor(D2D1::ColorF(r, g, b, a));
	m_pFillBrush->SetColor(D2D1::ColorF(r, g, b, a));

	D2D1_ELLIPSE ellipse = D2D1::Ellipse(
		D2D1::Point2F(x, y),
		xRadius,
		yRadius
	);
	m_pRenderTarget->DrawEllipse(ellipse, m_pMainBrush, strokesize);
	m_pRenderTarget->FillEllipse(ellipse, m_pFillBrush);
}


void Graphics::RenderSquareRGBA(float x, float y, float size, float r, float g, float b, float a, float strokesize) {
	m_pMainBrush->SetColor(D2D1::ColorF(r, g, b, a));

	D2D1_RECT_F square = D2D1::RectF(
		x - (size / 2),
		y - (size / 2),
		x + (size / 2),
		y + (size / 2)
	);
	m_pRenderTarget->DrawRectangle(square, m_pMainBrush, strokesize);
}

void Graphics::RenderSquareRGBAF(float x, float y, float size, float r, float g, float b, float a, float strokesize) {
	m_pMainBrush->SetColor(D2D1::ColorF(r, g, b, a));
	m_pFillBrush->SetColor(D2D1::ColorF(r, g, b, a));

	D2D1_RECT_F square = D2D1::RectF(
		x - (size / 2),
		y - (size / 2),
		x + (size / 2),
		y + (size / 2)
	);
	m_pRenderTarget->DrawRectangle(square, m_pMainBrush, strokesize);
	m_pRenderTarget->FillRectangle(square, m_pFillBrush);
}

void Graphics::RenderSquareRGBASF(float x, float y, float size, float r, float g, float b, float a, float strokesize, float fill_r, float fill_g, float fill_b, float fill_a) {
	m_pMainBrush->SetColor(D2D1::ColorF(r, g, b, a));
	m_pFillBrush->SetColor(D2D1::ColorF(fill_r, fill_g, fill_b, fill_a));

	D2D1_RECT_F square = D2D1::RectF(
		x - (size / 2),
		y - (size / 2),
		x + (size / 2),
		y + (size / 2)
	);
	m_pRenderTarget->DrawRectangle(square, m_pMainBrush, strokesize);
	m_pRenderTarget->FillRectangle(square, m_pFillBrush);
}
