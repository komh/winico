/* check.cmd */

'gmake.cmd'

if rc \= 0 then
    exit 1

sWinIconList = 'testcases\qmetrics.ico',
               'testcases\vlc.ico',
               'testcases\kalarm.ico'

call convert sWinIconList

exit 0

convert: procedure
    parse arg sWinIconList

    do until length( sWinIconList ) = 0
        sWinIconList = strip( sWinIconList )

        parse value sWinIconList with sWinIcon sWinIconList
        sOS2Icon = left( sWinIcon, length( sWinIcon ) - 4) || '_os2.ico'

        if stream( sOS2Icon, 'c', 'query exists') \= '' then
            'del' sOS2Icon

        say '----- Converting' sWinIcon
        'winico' sWinIcon sOS2Icon
    end

    return
