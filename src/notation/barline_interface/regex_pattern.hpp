#pragma once
#include <string>

const std::string RXPTN_SINGLENOTE { "\\(([A-G][#|b]?[0-7],[0-9]+/[0-9]+)(?:,\\[.*\\])?(?:,<.*>)?\\)" };

const std::string RXPTN_RESTNOTE { "\\((R|r)(est)?,[0-9]+/[0-9]+\\)" };

const std::string RXPTN_CHORD { "\\{\\([A-G][#|b]?[0-7],[0-9]+/[0-9]+(?:,\\[.*\\])?(?:,<.*>)?\\)(\\([A-G][#|b]?[0-7](,[0-9]+/[0-9]+)?\\))+\\}" };

const std::string RXPTN_PROPERTY { "\\[(?:.*\\:.*;)*(?:.*\\:.*)\\]" };

const std::string RXPTN_ORNAMENT { "<(.*(?:\\:.*)?)>" };