function dump(o)
    if type(o) == 'table' then
        local s = '{ '
        for k,v in pairs(o) do
            if type(k) ~= 'number' then k = '"'..k..'"' end
            s = s .. '['..k..'] = ' .. dump(v) .. ','
        end
        return s .. '} '
    else
        return tostring(o)
    end
end


function test(num, obj)
    local ttype = LE3Object.get_object_type(obj)
    print(ttype)
    local tbl = _G[ttype].save(obj)
    print(num)
    print(dump(tbl))
end