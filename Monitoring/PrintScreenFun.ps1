Function PrintScreenFun 
{
    [CmdletBinding()] Param(
            [Parameter(Mandatory=$True)]             
            [int32] $Interval,

            [Parameter(Mandatory=$True)]             
            [string] $FileName,

            [Parameter(Mandatory=$false)]
            [bool]$AddTimestamp=$false
            )

        Function PrintScreen 
        {
           $ScreenBounds = [Windows.Forms.SystemInformation]::VirtualScreen
           $ScreenshotObject = New-Object Drawing.Bitmap $ScreenBounds.Width, $ScreenBounds.Height
           $DrawingGraphics = [Drawing.Graphics]::FromImage($ScreenshotObject)
           $DrawingGraphics.CopyFromScreen($ScreenBounds.Location, [Drawing.Point]::Empty, $ScreenBounds.Size)
           if($AddTimestamp)
           {
                $Timestamp_Font = New-Object System.Drawing.Font("Segoe UI Bold", 69);
                $Timestamp_Brush_Fg = [System.Drawing.Brushes]::White;
                $Timestamp_Brush_Bg = [System.Drawing.Brushes]::Black;
        
                [String]$Timestamp_DateTimeString = Get-Date -UFormat "%d/%m/%Y %R";
                [String]$nazwamaszyny = hostname
                $Bobo = "$Timestamp_DateTimeString - $nazwamaszyny"

                $Timestamp_Font_BackgroundSize = $DrawingGraphics.MeasureString($Bobo, $Timestamp_Font);
                $Timestamp_Font_BackgroundRect = New-Object System.Drawing.RectangleF(100,900, $Timestamp_Font_BackgroundSize.Width, $Timestamp_Font_BackgroundSize.Height);
       
                $DrawingGraphics.FillRectangle($Timestamp_Brush_Bg, $Timestamp_Font_BackgroundRect);
                $DrawingGraphics.DrawRectangle($Timestamp_Brush_Fg, [System.Drawing.Rectangle]::Round($Timestamp_Font_BackgroundRect));
                $DrawingGraphics.DrawString($Bobo, $Timestamp_Font, $Timestamp_Brush_Fg, 100, 900);      
           }
           $DrawingGraphics.Dispose()
           $ScreenshotObject.Save($FilePath)
           $ScreenshotObject.Dispose()
        }
        Add-Type -Assembly System.Windows.Forms
        Add-Type -Assembly System.Drawing
        $Path = "na"
        While($true)
        {
            Try 
            {               
      
                Do 
                {
                    $FilePath = (Join-Path $Path $FileName)

                    PrintScreen
                    Start-Sleep -Seconds $Interval
                }
                While($true)
            }
         Catch {Write-Warning "$Error[0].ToString() + $Error[0].InvocationInfo.PositionMessage"}
        }
}

PrintScreenFun -Interval 20 -FileName Screen1.jpg -AddTimestamp $true

