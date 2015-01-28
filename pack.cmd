/* pack.cmd : packaging scripts not using version macros */

'@echo off'

/* Error if non-defined variables are used */
signal on novalue

parse arg sCmdLine

if sCmdLine = '' then
do
    say 'Usage: pack.cmd version [release-revision]'
    exit 1
end

/* ----- Configuration parts start ----- */

/* Base name of a package */
sPackageBase = 'winico'

/* Source directory to archive */
sSourceDir   = 'src'

/* File list to package */
sFileList    = 'winico.exe',
               'License.txt',
               'readme.txt'

/* File list to copy to a top directory for packaging */
sCopyList    = 'src\winico.exe'

/* ----- Configuration parts end ----- */

parse value sCmdLine with sVer sRev

/* Version + revision */
sVerRev      = sVer || sRev

/* Short version + revision */
sShortVerRev = removeNonNumber( sVer ) || sRev

/* File names for a package */
sPackage       = sPackageBase || sShortVerRev
sPackageZip    = sPackage || '.zip'
sPackageTxt    = sPackage || '.txt'

/* File name for a source zip */
sSourceZip = 'source.zip'

/* Remove an existing source zip */
'if exist' sSourceZip 'del' sSourceZip

/* Archive sources */
'git archive --format=zip -o' sSourceZip 'HEAD' sSourceDir

/* Create a package text */
'sed' '-e s/@SHORT_VER@/' || sShortVerRev || '/g',
      '-e s/@VER@/' || sVerRev || '/g',
      sPackageBase || '.txt' '>' sPackageTxt

/* Copy files necessary for packaging */
i = words( sCopyList )
do while i > 0
    'copy' word( sCopyList, i ) '.'

    i = i - 1
end /* do */

/* Remove an existing package zip */
'if exist' sPackageZip 'del' sPackageZip

/* Archive package files */
'zip' sPackageZip sFileList sSourceZip sPackageTxt 'donation.txt'

/* Remove files copied for packaging */
i = words( sCopyList )
do while i > 0
    'del' filespec('n', word( sCopyList, i ))

    i = i - 1
end /* do */

/* Remove an archived source zip for packaging */
'del' sSourceZip

exit 0

/* Remove non-number characters */
removeNonNumber: procedure
    parse arg sStr

    i = length( sStr )
    do while i > 0
        if datatype( substr( sStr, i, 1 ), 'n') = 0  then
            sStr = delstr( sStr, i, 1 )

        i = i - 1
    end /* do */

    return sStr
