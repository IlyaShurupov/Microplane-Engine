//============================================================================
// Microplane Engine - ME2D
//----------------------------------------------------------------------------
// Copyright (c) 2018, 2020 Ivan Kmeťo
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

#include "Graphics.hpp"
#include "CoreModule.hpp"


Graphics::Graphics()
{
	m_pFactory = NULL;
	m_pRenderTarget = NULL;
	m_pStrokeStyleDotted = NULL;
	m_pStrokeStyleDashed = NULL;
	m_pStrokeStyleDashDotted = NULL;
	m_pStrokeStyleDashDotDotted = NULL;
	m_pOutlineBrush = NULL;
	m_pFillBrush = NULL;
	m_pDWriteFactory = NULL;
	m_pTextFormat = NULL;
	m_pTextFormatMenu = NULL;
	m_pTextBrush = NULL;
}

Graphics::~Graphics()
{
	if (m_pTextBrush) m_pTextBrush->Release();
	if (m_pTextFormatMenu) m_pTextFormatMenu->Release();
	if (m_pTextFormat) m_pTextFormat->Release();
	if (m_pDWriteFactory) m_pDWriteFactory->Release();
	if (m_pStrokeStyleDashDotDotted) m_pStrokeStyleDashDotDotted->Release();
	if (m_pStrokeStyleDashDotted) m_pStrokeStyleDashDotted->Release();
	if (m_pStrokeStyleDashed) m_pStrokeStyleDashed->Release();
	if (m_pStrokeStyleDotted) m_pStrokeStyleDotted->Release();
	if (m_pFillBrush) m_pFillBrush->Release();
	if (m_pOutlineBrush) m_pOutlineBrush->Release();
	if (m_pRenderTarget) m_pRenderTarget->Release();
	if (m_pFactory) m_pFactory->Release();
}

bool Graphics::Init(HWND windowHandle)
{
	HRESULT errchck001 = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);
	if (errchck001 != S_OK) {
		ASSERT_ME2D(errchck001, "[ERRD2D1001] D2D1 Factory failed to initialize!", "Error");
		return false;
	}

	if (SUCCEEDED(errchck001)) {
		HRESULT errchck010 = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&m_pDWriteFactory));
		if (errchck010 != S_OK) {
			ASSERT_ME2D(errchck010, "[ERRDWRT001] DirectWrite Factory failed to initialize!", "Error");
			return false;
		}
	}

	RECT rect;
	GetClientRect(windowHandle, &rect);

	HRESULT errchck002 = m_pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)), &m_pRenderTarget);
	if (errchck002 != S_OK) {
		ASSERT_ME2D(errchck002, "[ERRD2D1002] D2D1 Factory failed to create ID2D1HwndRenderTarget!", "Error");
		return false;
	}

	HRESULT errchck003 = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &m_pOutlineBrush);
	if (errchck003 != S_OK) {
		ASSERT_ME2D(errchck003, "[ERRD2D1003] Failed to create Solid Color Brush!", "Error");
		return false;
	}

	HRESULT errchck004 = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &m_pFillBrush);
	if (errchck004 != S_OK) {
		ASSERT_ME2D(errchck004, "[ERRD2D1004] Failed to create Solid Color Brush!", "Error");
		return false;
	}


	//Stroke Styles
	D2D1_STROKE_STYLE_PROPERTIES strokeStylePropertiesDotted = D2D1::StrokeStyleProperties(
		D2D1_CAP_STYLE_FLAT,
		D2D1_CAP_STYLE_FLAT,
		D2D1_CAP_STYLE_TRIANGLE,
		D2D1_LINE_JOIN_MITER,
		10.0f,
		D2D1_DASH_STYLE_DOT,
		0.0f
	);
	HRESULT errchck015 = m_pFactory->CreateStrokeStyle(strokeStylePropertiesDotted, NULL, 0, &m_pStrokeStyleDotted);
	if (errchck015 != S_OK) {
		ASSERT_ME2D(errchck015, "[ERRD2D1006] Failed to create Stroke Style Dotted!", "Error");
		return false;
	}

	D2D1_STROKE_STYLE_PROPERTIES strokeStylePropertiesDashed = D2D1::StrokeStyleProperties(
		D2D1_CAP_STYLE_FLAT,
		D2D1_CAP_STYLE_FLAT,
		D2D1_CAP_STYLE_TRIANGLE,
		D2D1_LINE_JOIN_MITER,
		10.0f,
		D2D1_DASH_STYLE_DASH,
		0.0f
	);
	HRESULT errchck016 = m_pFactory->CreateStrokeStyle(strokeStylePropertiesDashed, NULL, 0, &m_pStrokeStyleDashed);
	if (errchck016 != S_OK) {
		ASSERT_ME2D(errchck016, "[ERRD2D1007] Failed to create Stroke Style Dashed!", "Error");
		return false;
	}

	D2D1_STROKE_STYLE_PROPERTIES strokeStylePropertiesDashDotted = D2D1::StrokeStyleProperties(
		D2D1_CAP_STYLE_FLAT,
		D2D1_CAP_STYLE_FLAT,
		D2D1_CAP_STYLE_TRIANGLE,
		D2D1_LINE_JOIN_MITER,
		10.0f,
		D2D1_DASH_STYLE_DASH_DOT,
		0.0f
	);
	HRESULT errchck017 = m_pFactory->CreateStrokeStyle(strokeStylePropertiesDashDotted, NULL, 0, &m_pStrokeStyleDashDotted);
	if (errchck017 != S_OK) {
		ASSERT_ME2D(errchck017, "[ERRD2D1008] Failed to create Stroke Style Dash-Dotted!", "Error");
		return false;
	}

	D2D1_STROKE_STYLE_PROPERTIES strokeStylePropertiesDashDotDotted = D2D1::StrokeStyleProperties(
		D2D1_CAP_STYLE_FLAT,
		D2D1_CAP_STYLE_FLAT,
		D2D1_CAP_STYLE_TRIANGLE,
		D2D1_LINE_JOIN_MITER,
		10.0f,
		D2D1_DASH_STYLE_DASH_DOT_DOT,
		0.0f
	);
	HRESULT errchck018 = m_pFactory->CreateStrokeStyle(strokeStylePropertiesDashDotDotted, NULL, 0, &m_pStrokeStyleDashDotDotted);
	if (errchck018 != S_OK) {
		ASSERT_ME2D(errchck018, "[ERRD2D1009] Failed to create Stroke Style Dash-Dot-Dotted!", "Error");
		return false;
	}


	//DirectWrite
	HRESULT errchck011 = m_pDWriteFactory->CreateTextFormat(
		L"Script",                   // Font family name.
		NULL,                        // Font collection (NULL sets it to use the system font collection)
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		12.0f,
		L"en-us",
		&m_pTextFormat
	);
	if (errchck011 != S_OK) {
		ASSERT_ME2D(errchck011, "[ERRDWRT002] DirectWrite Factory failed to create text format!", "Error");
		return false;
	}

	HRESULT errchck012 = m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	if (errchck012 != S_OK) {
		ASSERT_ME2D(errchck012, "[ERRDWRT003] Text Format failed to set alignment!", "Error");
		return false;
	}

	HRESULT errchck013 = m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	if (errchck013 != S_OK) {
		ASSERT_ME2D(errchck013, "[ERRDWRT004] Text Format failed to set paragraph alignment!", "Error");
		return false;
	}

	HRESULT errchck014 = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &m_pTextBrush);
	if (errchck014 != S_OK) {
		ASSERT_ME2D(errchck014, "[ERRD2D1005] Failed to create Solid Color Brush!", "Error");
		return false;
	}


	//TextFormatMenu
	HRESULT errchck019 = m_pDWriteFactory->CreateTextFormat(
		L"Script",                   // Font family name.
		NULL,                        // Font collection (NULL sets it to use the system font collection)
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		20.0f,
		L"en-us",
		&m_pTextFormatMenu
	);
	if (errchck019 != S_OK) {
		ASSERT_ME2D(errchck019, "[ERRDWRT005] DirectWrite Factory failed to create text format!", "Error");
		return false;
	}

	HRESULT errchck020 = m_pTextFormatMenu->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	if (errchck020 != S_OK) {
		ASSERT_ME2D(errchck020, "[ERRDWRT006] Text Format failed to set alignment!", "Error");
		return false;
	}

	HRESULT errchck021 = m_pTextFormatMenu->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	if (errchck021 != S_OK) {
		ASSERT_ME2D(errchck021, "[ERRDWRT007] Text Format failed to set paragraph alignment!", "Error");
		return false;
	}


	return true;
}


void Graphics::ClearScreen(float r, float g, float b)
{
	m_pRenderTarget->Clear(D2D1::ColorF(r, g, b));
}


void Graphics::RenderText(std::wstring text, float offsetX, float offsetY, float r, float g, float b, float a)
{
	m_pTextBrush->SetColor(D2D1::ColorF(r, g, b, a));

	std::wostringstream printString;
	printString << text;
	printText = printString.str();

	D2D1_RECT_F layoutRect = D2D1::RectF(offsetX, offsetY, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);

	m_pRenderTarget->DrawText(
		printText.c_str(),
		wcslen(printText.c_str()),
		m_pTextFormat,
		layoutRect,
		m_pTextBrush
	);
}

void Graphics::RenderTextMenu(std::wstring text, float offsetX, float offsetY, float r, float g, float b, float a)
{
	m_pTextBrush->SetColor(D2D1::ColorF(r, g, b, a));

	std::wostringstream printString;
	printString << text;
	printText = printString.str();

	D2D1_RECT_F layoutRect = D2D1::RectF(offsetX, offsetY, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);

	m_pRenderTarget->DrawText(
		printText.c_str(),
		wcslen(printText.c_str()),
		m_pTextFormatMenu,
		layoutRect,
		m_pTextBrush
	);
}


//-----------------------------------------------[OBJECTS: 2D GEOMETRY]-----------------------------------------------

void Graphics::DrawCircle(ME_TYPE2D_FILL fillType, ME_TYPE2D_OUTLINE outlineType, float outlineSize, float x, float y, float radius, float r, float g, float b, float a, float fill_r, float fill_g, float fill_b, float fill_a) {
	m_pOutlineBrush->SetColor(D2D1::ColorF(r, g, b, a));

	switch (fillType) {
	case ME2D_FILL_NONE:
		switch (outlineType) {
		case ME2D_OUTLINE_NONE:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pOutlineBrush, 0.0f);
			break;

		case ME2D_OUTLINE_SOLID:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pOutlineBrush, outlineSize);
			break;

		case ME2D_OUTLINE_DOTTED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDotted);
			break;

		case ME2D_OUTLINE_DASHED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashed);
			break;

		case ME2D_OUTLINE_DASH_DOTTED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotted);
			break;

		case ME2D_OUTLINE_DASH_DOT_DOTTED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotDotted);
			break;
		}
		break;

	case ME2D_FILL_PRIMARY:
		m_pFillBrush->SetColor(D2D1::ColorF(r, g, b, a));

		switch (outlineType) {
		case ME2D_OUTLINE_NONE:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pOutlineBrush, 0.0f);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_SOLID:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pOutlineBrush, outlineSize);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DOTTED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDotted);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASHED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashed);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOTTED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotted);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOT_DOTTED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotDotted);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pFillBrush);
			break;
		}
		break;

	case ME2D_FILL_SECONDARY:
		m_pFillBrush->SetColor(D2D1::ColorF(fill_r, fill_g, fill_b, fill_a));

		switch (outlineType) {
		case ME2D_OUTLINE_NONE:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pOutlineBrush, 0.0f);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_SOLID:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pOutlineBrush, outlineSize);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DOTTED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDotted);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASHED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashed);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOTTED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotted);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOT_DOTTED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotDotted);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_pFillBrush);
			break;
		}
		break;
	}
}

void Graphics::DrawEllipse(ME_TYPE2D_FILL fillType, ME_TYPE2D_OUTLINE outlineType, float outlineSize, float x, float y, float xRadius, float yRadius, float r, float g, float b, float a, float fill_r, float fill_g, float fill_b, float fill_a) {
	m_pOutlineBrush->SetColor(D2D1::ColorF(r, g, b, a));

	switch (fillType) {
	case ME2D_FILL_NONE:
		switch (outlineType) {
		case ME2D_OUTLINE_NONE:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pOutlineBrush, 0.0f);
			break;

		case ME2D_OUTLINE_SOLID:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pOutlineBrush, outlineSize);
			break;

		case ME2D_OUTLINE_DOTTED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDotted);
			break;

		case ME2D_OUTLINE_DASHED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashed);
			break;

		case ME2D_OUTLINE_DASH_DOTTED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotted);
			break;

		case ME2D_OUTLINE_DASH_DOT_DOTTED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotDotted);
			break;
		}
		break;

	case ME2D_FILL_PRIMARY:
		m_pFillBrush->SetColor(D2D1::ColorF(r, g, b, a));

		switch (outlineType) {
		case ME2D_OUTLINE_NONE:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pOutlineBrush, 0.0f);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_SOLID:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pOutlineBrush, outlineSize);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DOTTED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDotted);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASHED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashed);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOTTED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotted);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOT_DOTTED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotDotted);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pFillBrush);
			break;
		}
		break;

	case ME2D_FILL_SECONDARY:
		m_pFillBrush->SetColor(D2D1::ColorF(fill_r, fill_g, fill_b, fill_a));

		switch (outlineType) {
		case ME2D_OUTLINE_NONE:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pOutlineBrush, 0.0f);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_SOLID:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pOutlineBrush, outlineSize);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DOTTED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDotted);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASHED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashed);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOTTED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotted);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOT_DOTTED:
			m_pRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotDotted);
			m_pRenderTarget->FillEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), xRadius, yRadius), m_pFillBrush);
			break;
		}
		break;
	}
}

void Graphics::DrawSquare(ME_TYPE2D_FILL fillType, ME_TYPE2D_OUTLINE outlineType, float outlineSize, float x, float y, float size, float r, float g, float b, float a, float fill_r, float fill_g, float fill_b, float fill_a) {
	m_pOutlineBrush->SetColor(D2D1::ColorF(r, g, b, a));

	switch (fillType) {
	case ME2D_FILL_NONE:
		switch (outlineType) {
		case ME2D_OUTLINE_NONE:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pOutlineBrush, 0.0f);
			break;

		case ME2D_OUTLINE_SOLID:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pOutlineBrush, outlineSize);
			break;

		case ME2D_OUTLINE_DOTTED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDotted);
			break;

		case ME2D_OUTLINE_DASHED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashed);
			break;

		case ME2D_OUTLINE_DASH_DOTTED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotted);
			break;

		case ME2D_OUTLINE_DASH_DOT_DOTTED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotDotted);
			break;
		}
		break;

	case ME2D_FILL_PRIMARY:
		m_pFillBrush->SetColor(D2D1::ColorF(r, g, b, a));

		switch (outlineType) {
		case ME2D_OUTLINE_NONE:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pOutlineBrush, 0.0f);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pFillBrush);
			break;

		case ME2D_OUTLINE_SOLID:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pOutlineBrush, outlineSize);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DOTTED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDotted);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASHED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashed);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOTTED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotted);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOT_DOTTED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotDotted);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pFillBrush);
			break;
		}
		break;

	case ME2D_FILL_SECONDARY:
		m_pFillBrush->SetColor(D2D1::ColorF(fill_r, fill_g, fill_b, fill_a));

		switch (outlineType) {
		case ME2D_OUTLINE_NONE:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pOutlineBrush, 0.0f);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pFillBrush);
			break;

		case ME2D_OUTLINE_SOLID:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pOutlineBrush, outlineSize);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DOTTED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDotted);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASHED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashed);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOTTED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotted);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOT_DOTTED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotDotted);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), m_pFillBrush);
			break;
		}
		break;
	}
}

void Graphics::DrawSquareRounded(ME_TYPE2D_FILL fillType, ME_TYPE2D_OUTLINE outlineType, float outlineSize, float x, float y, float size, float radius, float r, float g, float b, float a, float fill_r, float fill_g, float fill_b, float fill_a) {
	m_pOutlineBrush->SetColor(D2D1::ColorF(r, g, b, a));

	switch (fillType) {
	case ME2D_FILL_NONE:
		switch (outlineType) {
		case ME2D_OUTLINE_NONE:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pOutlineBrush, 0.0f);
			break;

		case ME2D_OUTLINE_SOLID:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pOutlineBrush, outlineSize);
			break;

		case ME2D_OUTLINE_DOTTED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDotted);
			break;

		case ME2D_OUTLINE_DASHED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashed);
			break;

		case ME2D_OUTLINE_DASH_DOTTED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotted);
			break;

		case ME2D_OUTLINE_DASH_DOT_DOTTED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotDotted);
			break;
		}
		break;

	case ME2D_FILL_PRIMARY:
		m_pFillBrush->SetColor(D2D1::ColorF(r, g, b, a));

		switch (outlineType) {
		case ME2D_OUTLINE_NONE:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pOutlineBrush, 0.0f);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_SOLID:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pOutlineBrush, outlineSize);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DOTTED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDotted);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASHED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashed);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOTTED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotted);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOT_DOTTED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotDotted);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pFillBrush);
			break;
		}
		break;

	case ME2D_FILL_SECONDARY:
		m_pFillBrush->SetColor(D2D1::ColorF(fill_r, fill_g, fill_b, fill_a));

		switch (outlineType) {
		case ME2D_OUTLINE_NONE:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pOutlineBrush, 0.0f);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_SOLID:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pOutlineBrush, outlineSize);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DOTTED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDotted);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASHED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashed);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOTTED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotted);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOT_DOTTED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotDotted);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (size / 2), y - (size / 2), x + (size / 2), y + (size / 2)), radius, radius), m_pFillBrush);
			break;
		}
		break;
	}
}

void Graphics::DrawRect(ME_TYPE2D_FILL fillType, ME_TYPE2D_OUTLINE outlineType, float outlineSize, float x, float y, float width, float height, float r, float g, float b, float a, float fill_r, float fill_g, float fill_b, float fill_a) {
	m_pOutlineBrush->SetColor(D2D1::ColorF(r, g, b, a));

	switch (fillType) {
	case ME2D_FILL_NONE:
		switch (outlineType) {
		case ME2D_OUTLINE_NONE:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pOutlineBrush, 0.0f);
			break;

		case ME2D_OUTLINE_SOLID:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pOutlineBrush, outlineSize);
			break;

		case ME2D_OUTLINE_DOTTED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDotted);
			break;

		case ME2D_OUTLINE_DASHED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashed);
			break;

		case ME2D_OUTLINE_DASH_DOTTED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotted);
			break;

		case ME2D_OUTLINE_DASH_DOT_DOTTED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotDotted);
			break;
		}
		break;

	case ME2D_FILL_PRIMARY:
		m_pFillBrush->SetColor(D2D1::ColorF(r, g, b, a));

		switch (outlineType) {
		case ME2D_OUTLINE_NONE:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pOutlineBrush, 0.0f);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pFillBrush);
			break;

		case ME2D_OUTLINE_SOLID:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pOutlineBrush, outlineSize);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DOTTED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDotted);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASHED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashed);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOTTED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotted);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOT_DOTTED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotDotted);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pFillBrush);
			break;
		}
		break;

	case ME2D_FILL_SECONDARY:
		m_pFillBrush->SetColor(D2D1::ColorF(fill_r, fill_g, fill_b, fill_a));

		switch (outlineType) {
		case ME2D_OUTLINE_NONE:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pOutlineBrush, 0.0f);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pFillBrush);
			break;

		case ME2D_OUTLINE_SOLID:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pOutlineBrush, outlineSize);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DOTTED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDotted);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASHED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashed);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOTTED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotted);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOT_DOTTED:
			m_pRenderTarget->DrawRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotDotted);
			m_pRenderTarget->FillRectangle(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), m_pFillBrush);
			break;
		}
		break;
	}
}

void Graphics::DrawRectRounded(ME_TYPE2D_FILL fillType, ME_TYPE2D_OUTLINE outlineType, float outlineSize, float x, float y, float width, float height, float radius, float r, float g, float b, float a, float fill_r, float fill_g, float fill_b, float fill_a) {
	m_pOutlineBrush->SetColor(D2D1::ColorF(r, g, b, a));

	switch (fillType) {
	case ME2D_FILL_NONE:
		switch (outlineType) {
		case ME2D_OUTLINE_NONE:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pOutlineBrush, 0.0f);
			break;

		case ME2D_OUTLINE_SOLID:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pOutlineBrush, outlineSize);
			break;

		case ME2D_OUTLINE_DOTTED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDotted);
			break;

		case ME2D_OUTLINE_DASHED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashed);
			break;

		case ME2D_OUTLINE_DASH_DOTTED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotted);
			break;

		case ME2D_OUTLINE_DASH_DOT_DOTTED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotDotted);
			break;
		}
		break;

	case ME2D_FILL_PRIMARY:
		m_pFillBrush->SetColor(D2D1::ColorF(r, g, b, a));

		switch (outlineType) {
		case ME2D_OUTLINE_NONE:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pOutlineBrush, 0.0f);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_SOLID:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pOutlineBrush, outlineSize);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DOTTED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDotted);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASHED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashed);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOTTED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotted);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOT_DOTTED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotDotted);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pFillBrush);
			break;
		}
		break;

	case ME2D_FILL_SECONDARY:
		m_pFillBrush->SetColor(D2D1::ColorF(fill_r, fill_g, fill_b, fill_a));

		switch (outlineType) {
		case ME2D_OUTLINE_NONE:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pOutlineBrush, 0.0f);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_SOLID:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pOutlineBrush, outlineSize);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DOTTED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDotted);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASHED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashed);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOTTED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotted);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pFillBrush);
			break;

		case ME2D_OUTLINE_DASH_DOT_DOTTED:
			m_pRenderTarget->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotDotted);
			m_pRenderTarget->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2)), radius, radius), m_pFillBrush);
			break;
		}
		break;
	}
}

void Graphics::DrawLine(ME_TYPE2D_OUTLINE outlineType, float outlineSize, float point0X, float point0Y, float point1X, float point1Y, float r, float g, float b, float a) {
	m_pOutlineBrush->SetColor(D2D1::ColorF(r, g, b, a));

	switch (outlineType) {
	case ME2D_OUTLINE_NONE:
		m_pRenderTarget->DrawLine(D2D1::Point2F(point0X, point0Y), D2D1::Point2F(point1X, point1Y), m_pOutlineBrush, 0.0f);
		break;
	case ME2D_OUTLINE_SOLID:
		m_pRenderTarget->DrawLine(D2D1::Point2F(point0X, point0Y), D2D1::Point2F(point1X, point1Y), m_pOutlineBrush, outlineSize);
		break;

	case ME2D_OUTLINE_DOTTED:
		m_pRenderTarget->DrawLine(D2D1::Point2F(point0X, point0Y), D2D1::Point2F(point1X, point1Y), m_pOutlineBrush, outlineSize, m_pStrokeStyleDotted);
		break;

	case ME2D_OUTLINE_DASHED:
		m_pRenderTarget->DrawLine(D2D1::Point2F(point0X, point0Y), D2D1::Point2F(point1X, point1Y), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashed);
		break;

	case ME2D_OUTLINE_DASH_DOTTED:
		m_pRenderTarget->DrawLine(D2D1::Point2F(point0X, point0Y), D2D1::Point2F(point1X, point1Y), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotted);
		break;

	case ME2D_OUTLINE_DASH_DOT_DOTTED:
		m_pRenderTarget->DrawLine(D2D1::Point2F(point0X, point0Y), D2D1::Point2F(point1X, point1Y), m_pOutlineBrush, outlineSize, m_pStrokeStyleDashDotDotted);
		break;
	}
}
