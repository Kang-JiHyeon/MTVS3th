// Fill out your copyright notice in the Description page of Project Settings.


#include "KMK_ReceipWidget.h"
#include "../../../../Plugins/Runtime/WebBrowserWidget/Source/WebBrowserWidget/Public/WebBrowser.h"
#include "Components/TextBlock.h"
#include "Components/MultiLineEditableTextBox.h"

void UKMK_ReceipWidget::PlayYoutube(FString& url)
{
    url = TEXT("https://www.youtube.com/watch?v=NRgZuuwD2WY&list=RDNRgZuuwD2WY&start_radio=1");
    if (youtubeBrowser)
    {
        youtubeBrowser->LoadURL(url);
    }
}

void UKMK_ReceipWidget::SetTextLog(TMap<FString, FString> logs)
{
    MenuText->SetText(FText::FromString(logs["HI"]));
    IngredientText->SetText(FText::FromString(logs["He"]));
    ReceEdiableText->SetText(FText::FromString(logs["HIy"]));
}
