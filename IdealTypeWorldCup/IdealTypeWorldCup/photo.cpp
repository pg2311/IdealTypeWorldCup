#define _CRT_SECURE_NO_WARNINGS
#include "photo.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>
#include <codecvt>

// Names array definition
wchar_t names[20][100] = {
    L"차은우",
    L"이재욱",
    L"손종원",
    L"서강준",
    L"조규성",
    L"로운",
    L"사쿠야",
    L"원빈",
    L"장원영",
    L"윈터",
    L"민주",
    L"고윤정",
    L"김연아",
    L"한소희",
    L"김소혜",
    L"김지원"
};

void printphoto(int photo_no, int max_height, int skip_top)
{
    char path[256];
    sprintf(path, "imgs/%d.txt", photo_no);
    std::wifstream fp(path);
    fp.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
    if (!fp.is_open())
    {
        return;
    }

    // First, read all lines to determine total height
    std::vector<std::wstring> all_lines;
    std::wstring line;
    while (std::getline(fp, line))
    {
        all_lines.push_back(line);
    }
    fp.close();

    // Determine if we should skip lines (only if image is taller than max_height)
    int total_lines = (int)all_lines.size();
    int actual_skip = 0;
    if (max_height > 0 && total_lines > max_height)
    {
        actual_skip = skip_top;
    }

    // Extract the lines to display
    std::vector<std::wstring> lines;
    int start_line = actual_skip;
    int end_line = (max_height > 0) ? (start_line + max_height) : total_lines;
    if (end_line > total_lines)
        end_line = total_lines;

    for (int i = start_line; i < end_line; i++)
    {
        lines.push_back(all_lines[i]);
    }

    // Find the maximum width
    size_t fixed_width = 0;
    for (const auto& l : lines)
    {
        if (l.length() > fixed_width)
            fixed_width = l.length();
    }

    // Print all lines with fixed width
    for (const auto& l : lines)
    {
        std::wcout << l;
        // Pad to fixed width
        for (size_t j = l.length(); j < fixed_width; j++)
            std::wcout << L" ";
        std::wcout << std::endl;
    }
}

void printPhotoSideBySide(int left_photo, int right_photo, int selected, int trim_left, int trim_right, int max_height, int skip_top)
{
    // Read left photo - read all lines first
    char left_path[256];
    sprintf(left_path, "imgs/%d.txt", left_photo);
    std::wifstream left_fp(left_path);
    left_fp.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
    std::vector<std::wstring> left_all_lines;
    if (left_fp.is_open())
    {
        std::wstring line;
        while (std::getline(left_fp, line))
        {
            left_all_lines.push_back(line);
        }
        left_fp.close();
    }

    // Read right photo - read all lines first
    char right_path[256];
    sprintf(right_path, "imgs/%d.txt", right_photo);
    std::wifstream right_fp(right_path);
    right_fp.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
    std::vector<std::wstring> right_all_lines;
    if (right_fp.is_open())
    {
        std::wstring line;
        while (std::getline(right_fp, line))
        {
            right_all_lines.push_back(line);
        }
        right_fp.close();
    }

    // Determine if we should skip lines (only if image is taller than max_height)
    int left_total = (int)left_all_lines.size();
    int right_total = (int)right_all_lines.size();
    int actual_skip_left = 0;
    int actual_skip_right = 0;

    if (max_height > 0 && left_total > max_height)
    {
        actual_skip_left = skip_top;
    }
    if (max_height > 0 && right_total > max_height)
    {
        actual_skip_right = skip_top;
    }

    // Extract lines for left photo
    std::vector<std::wstring> left_lines;
    int left_start = actual_skip_left;
    int left_end = (max_height > 0) ? (left_start + max_height) : left_total;
    if (left_end > left_total)
        left_end = left_total;
    for (int i = left_start; i < left_end; i++)
    {
        left_lines.push_back(left_all_lines[i]);
    }

    // Extract lines for right photo
    std::vector<std::wstring> right_lines;
    int right_start = actual_skip_right;
    int right_end = (max_height > 0) ? (right_start + max_height) : right_total;
    if (right_end > right_total)
        right_end = right_total;
    for (int i = right_start; i < right_end; i++)
    {
        right_lines.push_back(right_all_lines[i]);
    }

    // Set fixed dimensions for all images
    size_t fixed_width = 0;
    size_t fixed_height = 0;

    // Calculate the actual width after trimming from both images
    for (const auto& line : left_lines)
    {
        int trimmed_length = (int)line.length() - trim_left - trim_right;
        if (trimmed_length > 0 && (size_t)trimmed_length > fixed_width)
            fixed_width = trimmed_length;
    }
    for (const auto& line : right_lines)
    {
        int trimmed_length = (int)line.length() - trim_left - trim_right;
        if (trimmed_length > 0 && (size_t)trimmed_length > fixed_width)
            fixed_width = trimmed_length;
    }

    // Set fixed height (use max_height if specified, otherwise use the max of both images)
    if (max_height > 0)
    {
        fixed_height = max_height;
    }
    else
    {
        fixed_height = (left_lines.size() > right_lines.size()) ? left_lines.size() : right_lines.size();
    }

    // Ensure we always display fixed_height lines (pad if necessary)
    size_t max_lines = fixed_height;

    // Print side by side
    for (size_t i = 0; i < max_lines; i++)
    {
        // Left side
        if (selected == 0)
            std::wcout << L">> ";
        else
            std::wcout << L"   ";

        if (i < left_lines.size())
        {
            std::wstring line = left_lines[i];
            // Trim the line
            int start = trim_left;
            int end = (int)line.length() - trim_right;
            if (start < end && start >= 0 && end <= (int)line.length())
            {
                std::wstring trimmed = line.substr(start, end - start);
                std::wcout << trimmed;
                // Pad to target width
                for (size_t j = trimmed.length(); j < fixed_width; j++)
                    std::wcout << L" ";
            }
            else
            {
                // Empty line - pad with spaces
                for (size_t j = 0; j < fixed_width; j++)
                    std::wcout << L" ";
            }
        }
        else
        {
            // No line - pad with spaces
            for (size_t j = 0; j < fixed_width; j++)
                std::wcout << L" ";
        }

        // Spacing between photos
        std::wcout << L" | ";

        // Right side
        if (selected == 1)
            std::wcout << L">> ";
        else
            std::wcout << L"   ";

        if (i < right_lines.size())
        {
            std::wstring line = right_lines[i];
            // Trim the line
            int start = trim_left;
            int end = (int)line.length() - trim_right;
            if (start < end && start >= 0 && end <= (int)line.length())
            {
                std::wstring trimmed = line.substr(start, end - start);
                std::wcout << trimmed;
                // Pad to target width
                for (size_t j = trimmed.length(); j < fixed_width; j++)
                    std::wcout << L" ";
            }
            else
            {
                // Empty line - pad with spaces
                for (size_t j = 0; j < fixed_width; j++)
                    std::wcout << L" ";
            }
        }
        else
        {
            // No line - pad with spaces
            for (size_t j = 0; j < fixed_width; j++)
                std::wcout << L" ";
        }

        std::wcout << std::endl;
    }
}